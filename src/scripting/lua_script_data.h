#pragma once
#include <base_types/base_types.h>
#include <utils/utils.h>
#include <core\core.h>

#include <Lua\lua.hpp>
#include <LuaBridge\LuaBridge.h>

class LuaScript
{
public:
	struct lua_State* lua_state = nullptr;

	std::map<cstr, luabridge::LuaRef*> stack;
	cstr path;
private:
	friend class LuaManager;
	luabridge::LuaRef init_method		= nullptr;
	luabridge::LuaRef update_method		= nullptr;
	luabridge::LuaRef destroy_method	= nullptr;

	void compile_success() {
		this->init_method		= get_func("init");
		this->update_method		= get_func("update");
		this->destroy_method	= get_func("destroy");
	}

	luabridge::LuaRef get_func(const cstr& name) {
		luabridge::LuaRef func = luabridge::getGlobal(lua_state, name.c_str());
		return func;
	}
public:
	template<typename T>
	void push_to_stack(const cstr& name, const T& extern_var) {
		luabridge::LuaRef* ref = mem::alloc<luabridge::LuaRef>(lua_state, extern_var);
		stack.insert(
			{ name, ref }
		);
	}
	template<typename T, typename... Args>
	T call_method(const cstr& name, Args&&... args) {
		luabridge::LuaRef func = this->get_func(name);
		if (!func.isFunction()) {
			core->fatal_error(utils::format(
				"Function is not a function. Name: %s", name
			));
		}
		return func(std::forward<Args>(args)...).cast<T>();
	}
public:
	void call_init() {
		this->init_method();
	}
	void call_update() {
		this->update_method();
	}
	void call_destroy() {
		this->destroy_method();
	}
};