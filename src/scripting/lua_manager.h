#pragma once
#include <string>
#include <map>

#include <base_types\base_types.h>
#include <utils\utils.h>
#include <core\core_module.h>

class LuaManager : ICoreModule
{
public:
	std::vector<struct LuaScript*> lua_scripts;
public:
	struct LuaScript* get_script(std::string path);
protected:
	friend class Core;
	void initiliaze() override;
	void destroy() override;
private:
	void parse_script_folder();
	void compile_all_scripts();
	void process_new_script(LuaScript* script);
	void register_base_functions(LuaScript* script);
};