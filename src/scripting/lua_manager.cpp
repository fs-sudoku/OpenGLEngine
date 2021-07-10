#include "lua_manager.h"

#include <core\core.h>
#include <utils\file_io.h>
#include <utils\utils.h>
#include <Lua\lua.hpp>

#include <LuaBridge\LuaBridge.h>
#include <LuaBridge\Vector.h>

using namespace luabridge;

template<typename T>
inline std::vector<T> get_list_from_lua(LuaRef& ref)
{
	std::vector<T> result;
	uint length = ref.length();

	if (!ref.isTable()) {
		core->fatal_error("Value is not table");
		return result;
	}
	for (size_t i = 0; i < length; i++) {
		result.push_back(ref[i + 1].cast<T>());
	}
	return result;
}

LuaScript* LuaManager::get_script(cstr path)
{
	return lua_script_by_path[RESOURCE_PATH(path)];
}

void LuaManager::initiliaze()
{
	this->parse_script_folder();
	this->compile_all_scripts();
}

void LuaManager::destroy()
{
	for (LuaScript* s : this->lua_scripts) {
		lua_close(s->lua_state);
		mem::free(s);
	}
}

void LuaManager::parse_script_folder()
{
	std::vector<std::string> all_scripts = utils::io::get_files_in_directory(
		utils::format(RESOURCE_PATH("scripts"))
	);
	for (const std::string p : all_scripts) {
		core->print(utils::format("Loaded script: %s", p.c_str()));

		LuaScript* script = mem::alloc<LuaScript>();
		script->path = p.c_str();

		this->process_new_script(script);
	}
}

void LuaManager::compile_all_scripts()
{
	for (LuaScript* s : lua_scripts) {
		int o_file_result = luaL_loadfile(
			s->lua_state, s->path.c_str()
		);

		int call_result = lua_pcall(s->lua_state, 0, 0, 0);

		if (o_file_result) {
			core->fatal_error(utils::format(
				"Lua API error: cannot open file: %s", lua_tostring(s->lua_state, -1)
			));
			lua_pop(s->lua_state, 1);
		}
		if (call_result) {
			core->fatal_error(utils::format(
				"Lua API error: %s", lua_tostring(s->lua_state, -1)
			));
			lua_pop(s->lua_state, 1);
		}
	}
}

void LuaManager::process_new_script(LuaScript* script)
{
	this->lua_scripts.push_back(script);
	this->lua_script_by_path.emplace(std::pair<std::string, LuaScript*>(
		script->path, script)
	);

	script->lua_state = luaL_newstate();

	luaL_openlibs(script->lua_state);
}