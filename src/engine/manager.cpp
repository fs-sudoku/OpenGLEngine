#include "manager.h"

#include <render\render.h>
#include <engine\camera.h>
#include <gameplay\actor.h>

Manager::Manager() { }

void Manager::initiliaze()
{
	this->camera = mem::alloc<Camera>();

	core->render->set_camera(camera);
	camera->transform.get_position() = vec3(0, 0, -4);

	this->actor = mem::alloc<Actor>(camera);
}

void Manager::process_update()
{
	for (IUpdatableObject* u : updatable_objects) {
		u->update();
	}
}

void Manager::destroy()
{
	mem::free(actor);
	mem::free(camera);
}