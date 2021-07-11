#pragma once
#include <stdio.h>

#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <typeinfo>
#include <base_types\base_types.h>

#define RESOURCE_PATH(PATH) utils::format("%s%s", "../gamedata/", PATH)
#define NAMEOF(VAR)			#VAR

namespace utils
{
	template<typename... Args>
	constexpr cstr format(const cstr format, Args... args)
	{
		const size_t lenght = 64 + strlen(format);
		char* buffer = mem::alloc_array<char>(lenght);
		sprintf_s(buffer, lenght, format, args...);
		return buffer;
	}
	extern void print_at_console(const cstr message);
}