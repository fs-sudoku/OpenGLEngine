#pragma once
#include <core\core_module.h>

#include <render\world_matrix.h>

struct	SDL_Window;
struct	SDL_Renderer;

class Render : ICoreModule
{
public:
	class ShaderProcessor*	shader_proc = nullptr;
public:
	REGISTER_PROPERTY(class Camera*, camera);
private:
	friend class Core;
private:
	bool			is_run			= true;
	vec2			size			= vec2(1366u, 728u);
	vec2			center			= size / 2.f;
	float			aspect			= size.x / size.y;
	uint			ticks			= 0u;
private:
	SDL_Window*		window_pattern	= nullptr;
	SDL_Renderer*	render_pattern	= nullptr;
	class Camera*	camera			= nullptr;
private:
	const WorldMatrix world_matrix	= {};
protected:
	void initiliaze() override;
	void process_update() override;
	void destroy() override;
private:
	void for_each_shaders();
	void pre_logic();
	void begin_render();
	void flush_render();
	void prepare_opengl();
};