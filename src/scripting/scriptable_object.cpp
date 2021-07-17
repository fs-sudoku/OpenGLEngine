#include "scriptable_object.h"

#include <core\core.h>
#include <scripting\lua_manager.h>

IScriptableObject::IScriptableObject(const cstr& script_name) : script_path(script_name)
{
	core->lua_manager->get_script_objects().push_back(this);
}