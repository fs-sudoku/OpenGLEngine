#include "file_io.h"
#include <core\core.h>

#include <stdio.h>
#include <fstream>
#include <filesystem>

cstr utils::io::read_file(const cstr& path)
{
	std::ifstream file(path);

	if (file.fail()) {
		core->fatal_error(utils::format(
			"Cannot open file! Path: %s", path.data())
		);
	}

	return cstr(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}