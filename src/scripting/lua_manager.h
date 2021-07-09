#pragma once
#include <base_types\base_types.h>

#include <core\core_module.h>

struct LuaScript
{
	cstr path					= nullptr;
	struct lua_State* lua_state = nullptr;
};

class LuaManager : ICoreModule
{
public:
	std::vector<LuaScript*> lua_scripts;
	std::vector<cstr> lua_singletons;
protected:
	friend class Core;
	void initiliaze() override;
	void destroy() override;
private:
	void parse_script_folder();
	void process_new_script(LuaScript* script);
	void process_global_script(LuaScript* script);
	void register_base_functions(LuaScript* script);
};