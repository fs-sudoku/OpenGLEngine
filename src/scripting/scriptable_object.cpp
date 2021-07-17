#include "scriptable_object.h"

#include <core\core.h>
#include <scripting\lua_manager.h>

IScriptableObject::IScriptableObject(const cstr& script_name)
{
	cstr c_script_name = RESOURCE_PATH(script_name.data());
	this->script = core->lua_manager->get_script(c_script_name);

	if (this->script == nullptr) {
		core->fatal_error(utils::format(
			"Script is null. Path: %s", c_script_name.data()
		));
	}
}