#include "file_io.h"
#include <core\core.h>

#include <stdio.h>
#include <fstream>
#include <filesystem>

cstr utils::io::read_file(const cstr path)
{
	std::ifstream file(path);

	if (file.fail()) {
		core->fatal_error(format("Cannot open file! Path: %s", path));
	}

	return cstr(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

std::vector<cstr> utils::io::get_files_in_directory(const cstr dir)
{
	namespace fs = std::filesystem;
	fs::recursive_directory_iterator b(dir), e;

	std::vector<fs::path> paths(b, e);
	std::vector<cstr> result;

	for (size_t i = 0; i < paths.size(); i++) {
		result.push_back(paths[i].string());
	}
	std::sort(result.begin(), result.end());
	return result;
}
