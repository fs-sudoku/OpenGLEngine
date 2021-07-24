#include "scriptable_module.h"

#include <core\core.h>
#include <scripting\lua_manager.h>

IScriptableModule::IScriptableModule(const cstr& script_name) : script_path(script_name)
{
	core->lua_manager->get_script_objects().push_back(this);
}