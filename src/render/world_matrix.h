#pragma once
#include <GLM\matrix.hpp>
#include <math\transform.h>

struct WorldMatrix
{
	mutable glm::mat4 view			= glm::mat4(1.0);
	mutable glm::mat4 projection	= glm::mat4(1.0);
	mutable glm::mat4 model			= glm::mat4(1.0);

	void create_matrix(Transform* transform, float aspect, float fov) const;
};