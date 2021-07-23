#pragma once
#include <utils\utils.h>

struct Transform
{
public:
	const vec3 world_up = vec3(0.0, 1.0, 0.0);
public:
	REGISTER_READ_ONLY_PROPERTY(vec3&, position);
	REGISTER_READ_ONLY_PROPERTY(vec3&, rotation);
	REGISTER_READ_ONLY_PROPERTY(vec3&, scale);
public:
	vec3 get_front();
	vec3 get_up(vec3 front, vec3 right);
	vec3 get_right(vec3 front);
private:
	vec3 position	= vec3(0.0f);
	vec3 rotation	= vec3(0.0f);
	vec3 scale		= vec3(0.0f);
};