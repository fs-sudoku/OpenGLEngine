#pragma once
#include <scripting\scriptable_module.h>
#include <engine\game_object.h>

#include <GLM\mat4x4.hpp>

class Camera : public GameObject, ISerializableObject
{
public:
	Camera();
	void update() override;
public:
	REGISTER_PROPERTY(float, fov);
	REGISTER_PROPERTY(float, sensity);
private:
	float fov = {};
	float sensity = {};
};