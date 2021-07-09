#include "lua_manager.h"

#include <core\core.h>
#include <utils\file_io.h>
#include <utils\utils.h>
#include <Lua\lua.hpp>
#include <LuaBridge/LuaBridge.h>

using namespace luabridge;

void LuaManager::initiliaze()
{
	this->parse_script_folder();
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

		process_new_script(script);
	}
}

void LuaManager::process_new_script(LuaScript* script)
{
	this->lua_scripts.push_back(script);
	script->lua_state = luaL_newstate();

	luaL_openlibs(script->lua_state);
	
	this->register_base_functions(script);

	int o_file_result = luaL_loadfile(
		script->lua_state, script->path
	);
	int call_result = lua_pcall(script->lua_state, 0, 0, 0);

	if (o_file_result) {
		core->fatal_error(utils::format(
			"Lua API error: cannot open file: %s", lua_tostring(script->lua_state, -1)
		));
		lua_pop(script->lua_state, 1);
	}
	if (call_result) {
		core->fatal_error(utils::format(
			"Lua API error: %s", lua_tostring(script->lua_state, -1)
		));
		lua_pop(script->lua_state, 1);
	}

	if (strstr(script->path, "_global") != false) {
		core->print(utils::format("Detected Lua global file, path: %s", script->path));
		this->process_global_script(script);
	}
}

void LuaManager::process_global_script(LuaScript* script)
{
	LuaRef singletons_ptr = getGlobal(script->lua_state, "_singleton_scripts");
	if (singletons_ptr.isNil()) {
		core->fatal_error("Cannot find list of singleton scripts!");
		return;
	}
	// std::vector<LuaRef> singletons = singletons_ptr.cast<std::vector<LuaRef>>();
}

void LuaManager::register_base_functions(LuaScript* script)
{
	getGlobalNamespace(script->lua_state)
		// register base functions
		.addFunction("print",			core->print)
		.addFunction("fatal_error",		core->fatal_error);
}