#pragma once
#include <gameplay\actor.h>
#include <engine\updatable_object.h>

class Actor : IUpdatableObject
{
public:
	Actor(class Camera* camera);
public:
	REGISTER_PROPERTY(class Camera*, camera);
	REGISTER_PROPERTY(float, speed);
private:
	void update() override;
private:
	float speed = 0.1f;
	class Camera* camera;
};