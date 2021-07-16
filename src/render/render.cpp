#include <core\core.h>
#include <render\render.h>	
#include <utils\utils.h>
#include <render\shader.h>
#include <render\shader_processor.h>
#include <engine\camera.h>

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <GLM\ext\matrix_transform.hpp>

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
	glewExperimental = GL_TRUE;
	if (uint gerr = glewInit() != NULL) {
		core->fatal_error(
			utils::format("Cannot initiliaze OpenGL. Log: %s", glewGetErrorString(gerr))
		);
	}
	this->shader_proc	= mem::alloc<ShaderProcessor>();
	this->prepare_opengl();
}

void Render::process_update()
{
	Shader shader(RESOURCE_PATH("shaders/basic/basic.glsl"));
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
		this->pre_logic();
		this->begin_render();
		{
			shader.use();
			glBegin(GL_POLYGON);
			glVertex3f(-0.6, -0.75, 0.5);
			glVertex3f(0.6, -0.75, 0);
			glVertex3f(0, 0.75, 0);
			glEnd();
		}
		this->flush_render();
	}
}

void Render::destroy()
{
	mem::free(shader_proc);

	SDL_DestroyWindow(this->window_pattern);
	SDL_DestroyRenderer(this->render_pattern);
	SDL_GL_DeleteContext(::gl_context_pattern);

	SDL_Quit();
}

void Render::for_each_shaders()
{
	for (auto* s : this->shader_proc->shaders) {
		s->set_base_uniforms(&world_matrix, ticks);
	}
}

void Render::pre_logic()
{
	this->ticks = SDL_GetTicks();
}

void Render::begin_render()
{
	glViewport(0, 0, size.x, size.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	world_matrix.create_matrix(&camera->transform, aspect, camera->get_fov());
	this->for_each_shaders();
	core->process_update();
}

void Render::flush_render()
{
	glFlush();
	SDL_GL_SwapWindow(this->window_pattern);
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