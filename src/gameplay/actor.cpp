#include "actor.h"

#include <render\render.h>

#include <engine\camera.h>
#include <engine\input.h>

Actor::Actor(Camera* camera) : camera(camera) 
{
	core->input->set_cursor_show(false);
	core->input->set_mouse_pos(core->render->get_center());
}

void Actor::update()
{
	const auto& center = core->render->get_center();
	const auto& mouse_pos = core->input->get_mouse_pos();
	const auto& offset = (mouse_pos - center) / (float) camera->get_sensity();
	core->input->set_mouse_pos(center);

	auto& rotation = camera->transform.get_rotation();
	auto& position = camera->transform.get_position();

	const auto& front = camera->transform.get_front();
	const auto& right = camera->transform.get_right(front);

	rotation.y += offset.x;
	rotation.x = glm::clamp(rotation.x - offset.y, -89.9f, 89.9f);

	if (core->input->is_key_pressed(Keys::KEY_W)) {
		position += front * (float)(speed * core->get_delta_time());
	}
	if (core->input->is_key_pressed(Keys::KEY_S)) {
		position -= front * (float)(speed * core->get_delta_time());
	}
	if (core->input->is_key_pressed(Keys::KEY_A)) {
		position -= right * (float)(speed * core->get_delta_time());
	}
	if (core->input->is_key_pressed(Keys::KEY_D)) {
		position += right * (float)(speed * core->get_delta_time());
	}
}