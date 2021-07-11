#include <core\core.h>
#include <utils\utils.h>
#include <memory\memory.h>
#include <render\render.h>
#include <engine\manager.h>
#include <scripting\lua_manager.h>

#include <SDL\SDL_messagebox.h>

Core::Core(bool is_editor, bool is_debug) : is_debug(is_debug), is_editor(is_editor) { }

void Core::initiliaze()
{
	this->render = register_core_module<Render>();

	this->lua_manager = register_core_module<LuaManager>();
	this->manager = register_core_module<Manager>();
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
	for (ICoreModule* m : this->core_modules) {
		if (m != render) {
			m->process_update();
		}
	}
}

void Core::destroy()
{	
	this->print("Destroying Main Core...");
	for (ICoreModule* m : this->core_modules) {
		m->destroy();
		mem::free(m);
	}
	if (!mem::allocated_memory.empty()) {
		for (mem::MemoryData p : mem::allocated_memory) {
			if (p.adress != this) {
				this->fatal_error(
					utils::format("Memory is not deleted! Adress: %p, Typename: %s", p.adress, p.type_name)
				);
			}
		}
	}
}

void Core::print(const cstr message)
{
	utils::print_at_console(message);
}

void Core::fatal_error(const cstr message)
{
	print(utils::format("Fatal error! Message: %s", message));
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR, "Fatal error corrupted", message.c_str(), nullptr
	);
}