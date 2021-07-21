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

std::vector<cstr> utils::io::get_files_in_directory(const cstr& dir) {
	using namespace std::filesystem;
	static std::vector<cstr> result;

	std::function<void(const cstr&)> parse_dir;
	parse_dir = [&parse_dir](const cstr& dir) {
		try {
			for (auto& p : recursive_directory_iterator(dir)) {
				auto full_path = p.path().string();
				if (p.is_directory()) {
					parse_dir(full_path.data());
					continue;
				}
				result.push_back(full_path);
			}
		}
		catch (const std::filesystem::filesystem_error& excp) {
			core->fatal_error(excp.what());
		}
	};
	parse_dir(dir);
	return result;
}