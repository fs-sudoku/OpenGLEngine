#include "scriptable_object.h"

#include <core\core.h>

IScriptableObject::IScriptableObject(cstr script_name)
{
	this->script = core->lua_manager->get_script(RESOURCE_PATH(script_name));
	if (this->script == nullptr) {
		core->fatal_error(utils::format(
			"Script is null. Path: %s", script_name
		));
	}
}