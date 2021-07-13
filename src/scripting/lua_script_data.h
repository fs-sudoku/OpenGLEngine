#pragma once
#include <base_types/base_types.h>
#include <utils/utils.h>
#include <core\core.h>

#include <Lua\lua.hpp>
#include <LuaBridge\LuaBridge.h>

struct LuaScript
{
	cstr path;
	std::map<cstr, luabridge::LuaRef*> stack;

	struct lua_State* lua_state = nullptr;

	template<typename T>
	void push_to_stack(const cstr& name, const T& extern_var) {
		luabridge::LuaRef* ref = mem::alloc<luabridge::LuaRef>(lua_state, extern_var);
		stack.insert(
			{ name, ref }
		);
	}
	void call_method(const cstr& name) {
		luabridge::LuaRef ref = luabridge::getGlobal(lua_state, name.c_str());
		if (!ref.isFunction()) {
			core->fatal_error(utils::format(
				"Called function is not a function. Name: %s", name
			));
		}
		ref();
	}
};