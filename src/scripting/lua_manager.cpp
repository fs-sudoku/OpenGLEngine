#include "lua_script_data.h"
#include "lua_manager.h"
#include "scriptable_object.h"

#include <core\core.h>
#include <utils\file_io.h>
#include <utils\utils.h>

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
	for (LuaScript* s : lua_scripts) {
		if (s->path == path) {
			return s;
		}
	}
	core->fatal_error(utils::format(
		"Cannot find script. Path: %s", path.c_str()
	));
	return nullptr;
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
		for (std::pair p : s->stack) {
			mem::free(p.second);
		}
		mem::free(s);
	}
}

void LuaManager::parse_script_folder()
{
	std::vector<cstr> all_scripts = utils::io::get_files_in_directory(
		RESOURCE_PATH("scripts/")
	);
	for (const cstr p : all_scripts) {
		core->print(utils::format("Loaded script: %s", p.c_str()));

		LuaScript* script = mem::alloc<LuaScript>();
		script->path = p.c_str();

		this->process_new_script(script);
	}
}

void LuaManager::compile_all_scripts()
{
	for (LuaScript* s : lua_scripts) {
		this->register_base_functions(s);

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
		s->compile_success();
	}
}

void LuaManager::process_new_script(LuaScript* script)
{
	this->lua_scripts.push_back(script);

	script->lua_state = luaL_newstate();

	luaL_openlibs(script->lua_state);
}

extern "C" int get_global_from_lua(lua_State * state)
{
	for (LuaScript* s : core->lua_manager->lua_scripts) {
		if (s->lua_state == state) {
			cstr arg = lua_tostring(state, 1);
			if (s->stack.find(arg) != s->stack.end()) {
				push(state, s->stack[arg]);
				return 1;
			} 
			else {
				core->fatal_error(utils::format(
					"Cannot get variable from Lua stack. Name: %s", arg
				));
			}
		}
	}
	return 1;
}

void LuaManager::register_base_functions(LuaScript* script)
{
	getGlobalNamespace(script->lua_state)
		.beginNamespace("utils")
			.addCFunction("get_extern",				::get_global_from_lua)
		.beginNamespace("io")
			.addFunction("read_file",				utils::io::read_file)
			.addFunction("get_files_in_directory",	utils::io::get_files_in_directory);
}