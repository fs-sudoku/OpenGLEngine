#include "manager.h"

void Manager::initiliaze()
{

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