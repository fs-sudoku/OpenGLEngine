#include <core\core.h>
#include <render\render.h>	
#include <utils\utils.h>
#include <render\shader.h>
#include <render\shader_processor.h>
#include <engine\camera.h>
#include <engine\input.h>
#include <render\mesh.h>

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <GLM\ext\matrix_transform.hpp>

static SDL_GLContext	gl_context_pattern;

Render::Render() : ISerializableObject("configs/user_config.json") { }

void Render::initiliaze()
{
	this->load_config();

	const auto& window_node = self_config->at("window");

	vec2 cfg_size = vec2(window_node["size-x"], window_node["size-y"]);
	this->update_screen_size(cfg_size);

	VERIFY(SDL_Init(SDL_INIT_EVERYTHING) == NULL);
	VERIFY(SDL_CreateWindowAndRenderer(size.x, size.y, SDL_WINDOW_OPENGL, &window_pattern, &render_pattern) == NULL);

	VERIFY(window_pattern != nullptr);
	VERIFY(render_pattern != nullptr);

	SDL_SetWindowTitle(this->window_pattern, "Application");

	gl_context_pattern = SDL_GL_CreateContext(window_pattern);
	glewExperimental = GL_TRUE;

	VERIFY(glewInit() == GLEW_OK);

	this->prepare_opengl();
}

void Render::process_update() noexcept
{
	Mesh test(RESOURCE_PATH("models/suzanne.obj"));
	Shader shader(RESOURCE_PATH("shaders/basic/basic.glsl"));
	shader.set_attached_trans(&test.transform);
	double old_time = SDL_GetTicks();
	while (is_run)
	{
		double new_time = SDL_GetTicks();
		double delta = new_time - old_time;

		SDL_Event event_pattern;
		while (SDL_PollEvent(&event_pattern))
		{
			if (event_pattern.type == SDL_QUIT) {
				is_run = false;
			}
			if (event_pattern.type == SDL_KEYDOWN) {
				core->input->pressed_keys[event_pattern.key.keysym.scancode] = true;
				if (event_pattern.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					is_run = false;
				}
			}
			if (event_pattern.type == SDL_KEYUP) {
				core->input->pressed_keys[event_pattern.key.keysym.scancode] = false;
			}
		}
		this->pre_logic();
		this->begin_render();
		{
			shader.use();
			test.draw();
		}
		this->flush_render();

		old_time = new_time;
		core->delta_time = delta;
	}
}

void Render::destroy()
{
	SDL_DestroyWindow(this->window_pattern);
	SDL_DestroyRenderer(this->render_pattern);
	SDL_GL_DeleteContext(::gl_context_pattern);

	SDL_Quit();
}

void Render::update_screen_size(vec2 size)
{
	this->size		= size;
	this->center	= vec2(size.x / 2.f, size.y / 2.f);
	this->aspect	= size.x / size.y;

	glViewport(0, 0, size.x, size.y);
}

inline void Render::for_each_shaders()
{
	for (auto* s : core->shader_proc->shaders) {
		s->set_base_uniforms(&world_matrix, ticks);
	}
}

inline void Render::pre_logic()
{
	core->process_update();
}

inline void Render::begin_render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	world_matrix.create_matrix(&camera->transform, aspect, camera->get_fov());
	this->for_each_shaders();
}

inline void Render::flush_render()
{
	glFlush();
	SDL_GL_SwapWindow(this->window_pattern);
}

void Render::prepare_opengl()
{
	// set fps lock to 60.0 in second
	SDL_GL_SetSwapInterval(1);

	glClearColor(0.3, 0.3, 0.3, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_MODELVIEW);
}