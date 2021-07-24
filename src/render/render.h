#pragma once
#include <core\core_module.h>
#include <serialization\serialization.h>

#include <render\world_matrix.h>

constexpr uint draw_mode_default	= 0x0004;
constexpr uint draw_mode_wireframe	= 0x0002;
constexpr uint draw_mode_points		= 0x0000;

struct	SDL_Window;
struct	SDL_Renderer;

class Render : ICoreModule, ISerializableObject
{
public:
	Render();
public:
	REGISTER_PROPERTY(class Camera*, camera);
	REGISTER_PROPERTY(uint, draw_mode);
	REGISTER_READ_ONLY_PROPERTY(auto*, window_pattern);
	REGISTER_READ_ONLY_PROPERTY(auto*, render_pattern);
	REGISTER_READ_ONLY_PROPERTY(auto, center);
	REGISTER_READ_ONLY_PROPERTY(auto, aspect);
	REGISTER_READ_ONLY_PROPERTY(auto, size);
private:
	friend class Core;
private:
	bool			is_run = true;
	vec2			size = vec2();
	vec2			center = vec2();
	float			aspect = {};
	uint			ticks = {};
	uint			draw_mode = {};
private:
	SDL_Window*		window_pattern = nullptr;
	SDL_Renderer*	render_pattern = nullptr;
	class Camera*	camera = nullptr;
private:
	const WorldMatrix world_matrix	= {};
protected:
	void initiliaze() override;
	void process_update() noexcept override;
	void destroy() override;
private:
	void update_screen_size(vec2 size);
	void for_each_shaders();
	void pre_logic();
	void begin_render();
	void flush_render();
	void prepare_opengl();
};