#include <engine\resource_manager.h>

#include <utils\file_io.h>

ResourceManager::ResourceManager()
{ }

std::vector<cstr> ResourceManager::convert_config_path(const cstr& path)
{
	std::vector<cstr> result;
	const auto converted_path = RESOURCE_PATH(path.data());
	if (!utils::find_in_string(converted_path, "*.")) {
		return { converted_path };
	}
	const cstr format = converted_path.substr(converted_path.find_last_of("."));
	const cstr only_dir = converted_path.substr(0, converted_path.find_last_of("*.") - 1);
	for (auto p : utils::io::get_files_in_directory(only_dir)) {
		if (utils::find_in_string(converted_path, format)) {
			result.push_back(p);
		}
	}
	return result;
}

void ResourceManager::initiliaze()
{

}

void ResourceManager::destroy()
{

}