#include <stdio.h>

#include "main.h"

#include "core\core.h"
#include "memory\memory.h"
#include "utils\utils.h"

Core* core;

int main(int argc, char* argv[])
{
	core = mem::alloc<Core>();

	core->printf("Last compile time: %s", LAST_COMPILE_TIME);
	core->printf("Executing in %s mode", is_editor ? "editor" : "standart");
	core->printf("Debug mode is %s", is_debug ? "on" : "off");

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