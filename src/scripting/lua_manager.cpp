#include "lua_script_data.h"
#include "lua_manager.h"
#include "scriptable_object.h"

#include <core\core.h>
#include <utils\file_io.h>
#include <utils\utils.h>
#include <filesystem>

#include <serialization\serialization.h>

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

LuaScript* LuaManager::get_script(const cstr& path)
{
	for (auto* s : lua_scripts) {
		if (s->path == path) {
			return s;
		}
	}
	core->fatal_error(utils::format(
		"Cannot find script. Path: %s", path.data()
	));
	return nullptr;
}

void LuaManager::initiliaze()
{
	this->load_all_scripts();
	this->compile_all_scripts();
}

void LuaManager::destroy()
{
	for (auto* s : this->lua_scripts) {
		lua_close(s->lua_state);
		for (std::pair p : s->stack) {
			mem::free(p.second);
		}
		mem::free(s);
	}
}

void LuaManager::load_all_scripts()
{
	std::vector<cstr> scripts = core->get_main_config()["scripts"];
	for (auto p : scripts) {
		auto converted_path = RESOURCE_PATH(p.data());
		auto script = mem::alloc<LuaScript>(converted_path);
		
		this->process_new_script(script);
		core->print(utils::format(
			"Loaded script. Path: %s", converted_path.data()), LogType::Sucess
		);
	}
}

void LuaManager::compile_all_scripts()
{
	for (auto* s : lua_scripts) {
		::register_base_functions(s);

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