#pragma once
#include <stdio.h>

#include <algorithm>
#include <vector>
#include <string>
#include <thread>
#include <map>
#include <type_traits>
#include <typeinfo>
#include <base_types\base_types.h>

#define RESOURCE_PATH(PATH) utils::format("%s%s", "../gamedata/", PATH)
#define MOD_PATH(PATH)		utils::format("%s%s", "../mods/", PATH)

#define NAMEOF(VAR)			#VAR

#define VEC2_TO_STR(VEC)	(utils::format("X: %f, Y: %f", VEC.x, VEC.y))
#define VEC3_TO_STR(VEC)	(utils::format("X: %f, Y: %f Z: %f", VEC.x, VEC.y, VEC.z))

#define REGISTER_PROPERTY(TYPE, NAME)	inline TYPE  get_##NAME()				{ return NAME;  } \
										inline void  set_##NAME(TYPE value)	{ NAME = value; }

#define REGISTER_READ_ONLY_PROPERTY(TYPE, NAME)	inline TYPE get_##NAME()		{ return NAME;  } \

enum class LogType
{
	Info	= 1u,
	Warning = 2u,
	Error	= 3u,
	Sucess	= 4u
};

namespace utils
{
	template<typename... Args>
	constexpr cstr format(const cstr& format, Args&&... args) noexcept
	{
		int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		auto size = static_cast<size_t>(size_s);
		auto buf = std::make_unique<char[]>(size);
		std::snprintf(buf.get(), size, format.c_str(), args...);
		return cstr(buf.get(), buf.get() + size - 1);
	}
	extern void print_at_console(const cstr& message, const LogType type = LogType::Info);
	extern bool find_in_string(const cstr& str, const cstr& find_element);
}