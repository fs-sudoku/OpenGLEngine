#pragma once
#include <core\core_module.h>

struct	SDL_Window;
struct	SDL_Renderer;

class Render : ICoreModule
{
public:
	class ShaderProcessor* shader_proc = nullptr;
private:
	friend class Core;
private:
	bool			is_run			= true;
	vec2			size			= vec2(1366u, 728u);
	vec2			center			= size / 2.f;
	float			aspect			= size.x / size.y;
	SDL_Window*		window_pattern	= nullptr;
	SDL_Renderer*	render_pattern	= nullptr;
protected:
	void initiliaze() override;
	void process_update() override;
	void destroy() override;
private:
	void prepare_opengl();
};