#pragma once
#include <gameplay\actor.h>
#include <engine\updatable_object.h>

class Actor : IUpdatableObject
{
public:
	Actor(class Camera* camera);
public:
	REGISTER_PROPERTY(class Camera*, camera);
private:
	void update() override;
private:
	class Camera* camera;
};