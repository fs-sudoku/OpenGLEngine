#include "manager.h"

#include <render\render.h>
#include <engine\camera.h>

Manager::Manager() : IScriptableObject("scripts/manager.lua") {	}

void Manager::initiliaze()
{
	core->render->set_camera(mem::alloc<Camera>());
	core->render->get_camera()->transform.position = vec3(0, 0, -7);
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