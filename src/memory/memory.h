#pragma once
#include <utils\utils.h>
#include <malloc.h>

#define BYTE_TO_BIT(x)	(x * 8u)
#define BYTE_TO_KB(x)	(x / 1024u)
#define BYTE_TO_MB(x)	((x / 1024u) / 1024u)

namespace mem
{
	struct MemoryData
	{
		cstr	type_name;
		void*	adress;

		bool operator==(void* adress) {
			return this->adress == adress;
		}
	};
	extern uint total_allocated;
	extern std::vector<MemoryData> allocated_memory;

	template<typename T, typename... Args>
	T* alloc(Args&&... args)
	{
		T* result = new T(std::forward<Args>(args)...);
		mem::total_allocated += sizeof(T);
		mem::allocated_memory.push_back({ typeid(T).name(), static_cast<void*>(result) });
		return result;
	}
	template<typename T>
	T* alloc_array(const size_t& size = 16u, bool add_to_stack = true)
	{
		T* result = new T[size];
		if (add_to_stack) {
			mem::allocated_memory.push_back({ typeid(T).name(), static_cast<void*>(result) });
		}
		return result;
	}
	template<typename T>
	void free(T* target) noexcept
	{
		mem::allocated_memory.erase(std::remove(
			allocated_memory.begin(), allocated_memory.end(),
			static_cast<void*>(target)), allocated_memory.end()
		);
		delete target;
		target = nullptr;
	}
}