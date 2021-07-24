#include <stdio.h>
#include <filesystem>
#include <functional>
#include <memory\memory.h>
#include <base_types\base_types.h>

#include "utils.h"

/*
			foreground	background
	black        30         40
	red          31         41
	green        32         42
	yellow       33         43
	blue         34         44
	magenta      35         45
	cyan         36         46
	white        37         47

*/

#if IS_DEBUG

const std::map<const LogType, const char*> log_type_by_color_ptr =
{
	{ LogType::Info,		"\033[1m\033[37m"	},
	{ LogType::Sucess,		"\033[32m"			},
	{ LogType::Error,		"\033[31m"			},
	{ LogType::Warning,		"\033[33m"			}
};

const std::map<const LogType, const char*> log_type_by_str =
{
	{ LogType::Info,		"INFO"		},
	{ LogType::Sucess,		"SUCESS"	},
	{ LogType::Error,		"ERROR"		},
	{ LogType::Warning,		"WARNING"	}
};

void utils::print_at_console(const cstr& message, const LogType type)
{
	auto color_ptr	= log_type_by_color_ptr.at(type);
	auto type_str	= log_type_by_str.at(type);

	auto result		= printf(
		"%s[%s] %s%s\n", color_ptr, type_str, message.data(), log_type_by_color_ptr.at(LogType::Info)
	);
}

#else

inline void utils::print_at_console(const cstr& message, const LogType type) { return; }

#endif

inline bool utils::find_in_string(const cstr& str, const cstr& find_element)
{
	return str.find(find_element) != cstr::npos;
}