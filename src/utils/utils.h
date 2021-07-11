#pragma once
#include <stdio.h>

#include <algorithm>
#include <vector>
#include <string>
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
		char buffer[128];
		sprintf_s(buffer, 128, format, args...);
		return (cstr)buffer;
	}
	extern void print_at_console(const cstr message);
}