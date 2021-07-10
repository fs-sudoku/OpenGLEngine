#include <stdio.h>

#include "main.h"

#include "core\core.h"
#include "memory\memory.h"
#include "utils\utils.h"

Core* core;

int main(int argc, char* argv[])
{
	bool is_editor	= static_cast<bool>(IS_EDITOR);
	bool is_debug	= static_cast<bool>(IS_DEBUG);

	core = mem::alloc<Core>(is_editor, is_debug);

	core->print(utils::format("Last compile time: %s", LAST_COMPILE_TIME));
	core->print(utils::format("Executing in %s mode", is_editor ? "editor" : "standart"));
	core->print(utils::format("Debug mode is %s", is_debug ? "on" : "off"));

	try 
	{
		core->initiliaze();
		core->start_update_in_render();
		core->destroy();
	}
	catch (const std::exception& excp) 
	{
		core->register_std_exception(excp);
	}

	mem::free(core);
	return 0;
}