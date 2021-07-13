#pragma once
#include <scripting\scriptable_object.h>
#include <engine\updatable_object.h>

class Camera : IScriptableObject, IUpdatableObject
{
public:
	Camera();
};