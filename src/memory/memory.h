#pragma once
#include <utils\utils.h>
#include <malloc.h>

namespace mem
{
	struct MemoryData
	{
		cstr type_name;
		void* adress;
		bool operator==(void* adress) {
			return this->adress == adress;
		}
	};
	extern std::vector<MemoryData> allocated_memory;
	template<typename T, typename... Args>
	inline T* alloc(Args&&... args)
	{
		T* result = new T(args...);
		allocated_memory.push_back({ typeid(T).name(), static_cast<void*>(result) });
		return result;
	}
	template<typename T>
	inline T* alloc_array(const size_t& size = 16u, bool add_to_stack = true)
	{
		T* result = new T[size];
		if (add_to_stack) {
			allocated_memory.push_back({ typeid(T).name(), static_cast<void*>(result) });
		}
		return result;
	}
	template<typename T>
	inline void free(T* target) noexcept
	{
		allocated_memory.erase(std::remove(
			allocated_memory.begin(), allocated_memory.end(),
			static_cast<void*>(target)), allocated_memory.end()
		);
		delete target;
		target = nullptr;
	}
}