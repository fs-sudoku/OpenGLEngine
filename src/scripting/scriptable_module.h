#pragma once
#include <scripting\lua_script_data.h>
#include <base_types\base_types.h>

class IScriptableModule
{
public:
	IScriptableModule(const cstr& script_name);
protected:
	friend class LuaManager;
	LuaScript* script = nullptr;
	cstr script_path;
};