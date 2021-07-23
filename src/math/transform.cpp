#include <math\transform.h>
#include <GLM\glm.hpp>

vec3 Transform::get_front()
{
	vec3 front;
	float pitch = rotation.x;
	float yaw = rotation.y;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	return glm::normalize(front);
}

vec3 Transform::get_up(vec3 front, vec3 right)
{
	return glm::normalize(glm::cross(right, front));
}

vec3 Transform::get_right(vec3 front)
{
	return glm::normalize(glm::cross(front, world_up));
}
