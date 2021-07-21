#include "updatable_object.h"

#include <engine\manager.h>
#include <core\core.h>

IUpdatableObject::IUpdatableObject()
{
	core->manager->get_updatable_objects().push_back(this);
}

IUpdatableObject::~IUpdatableObject()
{
	auto upd_objects_ref = core->manager->get_updatable_objects();
	auto iterator = std::remove(upd_objects_ref.begin(), upd_objects_ref.end(), this);
}