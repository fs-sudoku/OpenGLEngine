#include <engine\input.h>
#include <render\render.h>
#include <core\core.h>
#include <SDL\SDL_mouse.h>

bool Input::is_key_pressed(const Keys key)
{
	return this->pressed_keys[static_cast<uint>(key)];
}

vec2 Input::get_mouse_pos()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return vec2(x, y);
}

void Input::set_mouse_pos(vec2 pos)
{
	SDL_WarpMouseInWindow(core->render->get_window_pattern(), pos.x, pos.y);
}

void Input::set_cursor_show(bool value)
{
	SDL_ShowCursor(value);
}
