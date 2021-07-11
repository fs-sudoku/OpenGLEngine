#include "updatable_object.h"

#include <engine\manager.h>
#include <core\core.h>

IUpdatableObject::IUpdatableObject()
{
	core->manager->updatable_objects.push_back(this);
}

IUpdatableObject::~IUpdatableObject()
{
	auto iterator = std::remove(
		core->manager->updatable_objects.begin(),
		core->manager->updatable_objects.end(),
		this
	);
}