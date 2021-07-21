#include "manager.h"

#include <render\render.h>
#include <engine\camera.h>
#include <gameplay\actor.h>

Manager::Manager() { }

void Manager::initiliaze()
{
	core->render->set_camera(mem::alloc<Camera>());
	core->render->get_camera()->transform.position = vec3(0, 0, -7);
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