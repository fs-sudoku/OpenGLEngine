#pragma once
#include <base_types\base_types.h>
#include <utils\utils.h>
#include <string>

namespace utils
{
	namespace io
	{
		extern cstr read_file(const cstr& path);
		extern std::vector<cstr> get_files_in_directory(const cstr& dir);
	}
}