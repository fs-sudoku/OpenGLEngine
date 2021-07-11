#pragma once
#include <base_types/base_types.h>
#include <utils/utils.h>
#include <core\core.h>

#include <Lua\lua.hpp>
#include <LuaBridge\LuaBridge.h>

struct LuaScript
{
	cstr path;
	std::map<cstr, cstr> stack;

	struct lua_State* lua_state = nullptr;

	void push_to_stack(const cstr name, const cstr extern_var) {
		stack.insert(
			{ name, extern_var }
		);
	}
	void call_method(const cstr name) {
		luabridge::LuaRef ref = luabridge::getGlobal(lua_state, name.c_str());
		if (!ref.isFunction()) {
			core->fatal_error(utils::format(
				"Called function is not a function. Name: %s", name
			));
		}
		ref();
	}
};