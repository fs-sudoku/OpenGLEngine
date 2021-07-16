#include <scripting\lua_manager.h>
#include <scripting\lua_script_data.h>

#include <core\core.h>
#include <utils\file_io.h>

#include <render\render.h>

#include <GL\glew.h>

using namespace luabridge;

auto get_src_dir_prop = [](lua_State* s) -> int {
	lua_pushstring(s, "../gamedata/");
	return 1;
};

auto get_global_from_lua = [](lua_State* state) -> int {
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
};

uint get_uniform_location(uint id, const char* name) {
	return glGetUniformLocation(id, name);
};

void register_base_functions(LuaScript* script)
{
	auto gns = getGlobalNamespace(script->lua_state);
		// utils functions
		gns.beginNamespace("utils")
			.addCFunction("get_extern", ::get_global_from_lua)
			.addFunction("read_file", utils::io::read_file)
			.addFunction("get_files_in_directory", utils::io::get_files_in_directory)
			.addProperty("src_dir", get_src_dir_prop)
		.endNamespace()
		.beginNamespace("render")
			.addFunction("get_uniform_location", get_uniform_location)
		.endNamespace()
			.addFunction("fatal_error", core->fatal_error)
			.addFunction("print", core->print);
}