#pragma once
#include <scripting\scriptable_object.h>
#include <engine\game_object.h>

#include <GLM\mat4x4.hpp>

class Camera : public GameObject, IScriptableObject
{
public:
	Camera();
	void update() override;
public:
	REGISTER_PROPERTY(float, fov);
private:
	float fov = 45.0f;
};