#pragma once
#include <core\core_module.h>

struct	SDL_Window;
struct	SDL_Renderer;

class Render : ICoreModule
{
private:
	friend class Core;
private:
	bool			is_run			= true;
	uint			size_x			= 1366u;
	uint			size_y			= 728u;
	SDL_Window*		window_pattern	= nullptr;
	SDL_Renderer*	render_pattern	= nullptr;
protected:
	void initiliaze() override;
	void process_update() override;
	void destroy() override;
private:
	void prepare_opengl();
};