#include "manager.h"

Manager::Manager() : IScriptableObject("scripts/manager.lua") {	}

void Manager::initiliaze()
{
	script->call_init();
}

void Manager::process_update()
{
	script->call_update();
	for (IUpdatableObject* u : updatable_objects) {
		u->update();
	}
}

void Manager::destroy()
{
	script->call_destroy();
	for (IUpdatableObject* u : updatable_objects) {
		if (u != nullptr) {
			mem::free(u);
		} 
	}
}