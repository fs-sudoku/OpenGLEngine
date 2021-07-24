#include "config_manager.h"

#include <utils\file_io.h>
#include <engine\resource_manager.h>

void ConfigManager::initiliaze()
{
	std::vector<cstr> pathes = core->get_main_config()["configs"];
	for (const auto& p : pathes) {
		for (const cstr& c : core->src_manager->convert_config_path(p)) {
			this->all_configs.insert(
				{ c, Json::parse(utils::io::read_file(c), nullptr, true, true) }
			);
			core->printf("Loaded config. Path: %s", LogType::Sucess, c.data());
		}
	}
}

void ConfigManager::destroy()
{

}