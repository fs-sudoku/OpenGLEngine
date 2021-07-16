#include <render\world_matrix.h>

#include <GLM\glm.hpp>
#include <GLM\ext\matrix_clip_space.hpp>
#include <GLM\gtx\transform.hpp>

void WorldMatrix::create_matrix(Transform* transform, float aspect, float fov) const
{
    this->projection = glm::perspective(glm::radians(fov), aspect, 0.1f, 1000.0f);

	this->view = glm::translate(transform->position);
}