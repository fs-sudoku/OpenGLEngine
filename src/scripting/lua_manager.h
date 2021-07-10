#pragma once
#include <string>
#include <map>

#include <base_types\base_types.h>
#include <utils\utils.h>
#include <core\core_module.h>

struct LuaScript
{
	std::string path;
	struct lua_State* lua_state = nullptr;
};

class LuaManager : ICoreModule
{
public:
	std::vector<LuaScript*> lua_scripts;
	std::map<std::string, LuaScript*> lua_script_by_path;
public:
	LuaScript* get_script(cstr path);
protected:
	friend class Core;
	void initiliaze() override;
	void destroy() override;
private:
	void parse_script_folder();
	void compile_all_scripts();
	void process_new_script(LuaScript* script);
};