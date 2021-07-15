#pragma once
#include <base_types\object.h>
#include <engine\updatable_object.h>
#include <math\transform.h>

class GameObject : IUpdatableObject
{
public:
	Transform transform = {};
};