#include "manager.h"

Manager::Manager() : IScriptableObject("scripts/manager.lua") {	}

void Manager::initiliaze()
{
	script->call_method("init");
}

void Manager::process_update()
{
	for (IUpdatableObject* u : updatable_objects) {
		u->update();
	}
}

void Manager::destroy()
{
	for (IUpdatableObject* u : updatable_objects) {
		if (u != nullptr) {
			mem::free(u);
		} 
	}
}