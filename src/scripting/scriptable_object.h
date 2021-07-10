#pragma once
#include <scripting\lua_manager.h>
#include <scripting\lua_script_data.h>

class IScriptableObject
{
protected:
	IScriptableObject(cstr script_name);
protected:
	friend class LuaManager;
	LuaScript* script;
};