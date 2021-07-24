#pragma once
#include <string>
#include <map>

#include <base_types\base_types.h>
#include <utils\utils.h>
#include <core\core_module.h>

extern void register_base_functions(class LuaScript* script);

class LuaManager : ICoreModule
{
private:
	std::vector<class LuaScript*> lua_scripts;
	std::vector<class IScriptableModule*> script_objects;
public:
	REGISTER_READ_ONLY_PROPERTY(auto&, lua_scripts);
	REGISTER_READ_ONLY_PROPERTY(auto&, script_objects);
public:
	class LuaScript* get_script(const cstr& path);
protected:
	friend class Core;
	void initiliaze() override;
	void destroy() override;
private:
	void load_all_scripts();
	void compile_all_scripts();
	void apply_all_script_objects();
	void process_new_script(LuaScript* script);
};