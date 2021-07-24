#include "camera.h"

Camera::Camera() : ISerializableObject("configs/user_config.json")
{
	this->load_config();

	const auto& gameplay_node = self_config->at("gameplay");

	this->sensity = gameplay_node["sensity"];
	this->fov = gameplay_node["fovy"];
}

void Camera::update()
{

}