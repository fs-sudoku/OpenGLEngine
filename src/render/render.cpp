#include <core\core.h>
#include <render\render.h>	
#include <utils\utils.h>
#include <render\shader.h>

#include <SDL\SDL.h>
#include <GL\glew.h>

static SDL_GLContext	gl_context_pattern;

void Render::initiliaze()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL) {
		core->fatal_error(
			utils::format("Cannot initiliaze SDL. Log: %s", SDL_GetError())
		);
	}
	int serr = SDL_CreateWindowAndRenderer(
		size.x, size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, &window_pattern, &render_pattern
	);
	SDL_SetWindowTitle(this->window_pattern, "Application");
	if (serr != NULL) {
		core->fatal_error(
			utils::format("Cannot create SDL Window. Log: %s", SDL_GetError())
		);
	}
	gl_context_pattern = SDL_GL_CreateContext(window_pattern);
	if (uint gerr = glewInit() != NULL) {
		core->fatal_error(
			utils::format("Cannot initiliaze OpenGL. Log: %s", glewGetErrorString(gerr))
		);
	}
	this->prepare_opengl();
}

void Render::process_update()
{
	Shader shader(
		RESOURCE_PATH("shaders/standart_vertex.glsl"),
		RESOURCE_PATH("shaders/standart_fragment.glsl")
	);
	while (is_run)
	{
		SDL_Event event_pattern;
		while (SDL_PollEvent(&event_pattern))
		{
			if (event_pattern.type == SDL_QUIT) {
				is_run = false;
			}
			if (event_pattern.type == SDL_WINDOWEVENT) {
				if (event_pattern.window.type == SDL_WINDOWEVENT_RESIZED) {
					this->size = vec2(event_pattern.window.data1, event_pattern.window.data2);
					this->aspect = size.x / size.y;
					this->center = size / 2.f;
				}
			}
			if (event_pattern.type == SDL_KEYDOWN) {
				if (event_pattern.key.keysym.scancode == SDLK_ESCAPE) {
					is_run = false;
				}
			}
		}
		glViewport(0, 0, size.x, size.y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		core->process_update();
		shader.use();
		glBegin(GL_POLYGON);
		glVertex3f(-0.6, -0.75, 0.5);
		glVertex3f(0.6, -0.75, 0);
		glVertex3f(0, 0.75, 0);
		glEnd();
		glFlush();
		SDL_GL_SwapWindow(this->window_pattern);
	}
}

void Render::destroy()
{
	SDL_DestroyWindow(this->window_pattern);
	SDL_DestroyRenderer(this->render_pattern);
	SDL_GL_DeleteContext(::gl_context_pattern);

	SDL_Quit();
}

void Render::prepare_opengl()
{
	glClearColor(0, 0, 0, 0.f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}