#include <core\core.h>
#include <utils\utils.h>
#include <memory\memory.h>
#include <render\render.h>
#include <engine\manager.h>
#include <scripting\lua_manager.h>
#include <serialization\serialization.h>
#include <utils\file_io.h>
#include <engine\resource_manager.h>

#include <SDL\SDL_messagebox.h>

void Core::initiliaze()
{
	this->main_config = Json::parse(
		utils::io::read_file(RESOURCE_PATH("config.json"))
	);

	this->lua_manager = register_core_module<LuaManager>();
	this->lua_manager->initiliaze();

	this->render		= register_core_module<Render>();
	this->manager		= register_core_module<Manager>();

	for (auto* m : core_modules) {
		if (m != lua_manager) {
			m->initiliaze();
		}
	}
}

void Core::start_update_in_render()
{
	render->process_update();
}

void Core::register_std_exception(const std::exception& excp)
{
	this->fatal_error(utils::format(
		"Unhandled exception: %s", excp.what()
	));
}

void Core::process_update()
{
	for (auto* m : this->core_modules) {
		if (m != render) {
			m->process_update();
		}
	}
}

void Core::destroy()
{	
	std::reverse(core_modules.begin(), core_modules.end());
	for (auto* m : core_modules) {
		m->destroy();
		mem::free(m);
	}
	if (!mem::allocated_memory.empty()) {
		for (auto p : mem::allocated_memory) {
			if (p.adress != this) {
				this->fatal_error(
					utils::format(
						"Memory is not deleted! Adress: %p, Typename: %s", p.adress, p.type_name.data()
					)
				);
			}
		}
	}
}

void Core::print(const cstr& message)
{
	utils::print_at_console(message);
}

void Core::fatal_error(const cstr& message)
{
	print(utils::format("Fatal error! Message: %s", message.data()));
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR, "Fatal error corrupted", message.data(), nullptr
	);
}