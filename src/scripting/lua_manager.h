#pragma once
#include <string>
#include <map>

#include <base_types\base_types.h>
#include <utils\utils.h>
#include <core\core_module.h>

extern void register_base_functions(class LuaScript* script);

class LuaManager : ICoreModule
{
public:
	std::vector<class LuaScript*> lua_scripts;
public:
	class LuaScript* get_script(const cstr& path);
protected:
	friend class Core;
	void initiliaze() override;
	void destroy() override;
private:
	void load_all_scripts();
	void compile_all_scripts();
	void process_new_script(LuaScript* script);
};