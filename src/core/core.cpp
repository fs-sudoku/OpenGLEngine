#include <core\core.h>
#include <utils\utils.h>
#include <memory\memory.h>
#include <render\render.h>
#include <engine\manager.h>
#include <scripting\lua_manager.h>
#include <serialization\serialization.h>
#include <utils\file_io.h>
#include <engine\resource_manager.h>
#include <render\shader_processor.h>
#include <engine\input.h>
#include <engine\config_manager.h>

#include <SDL\SDL_messagebox.h>

void Core::initiliaze()
{
	this->main_config = Json::parse(
		utils::io::read_file(RESOURCE_PATH("config.json"))
	);

	this->lua_manager	= register_core_module<LuaManager>();
	this->cfg_manager	= register_core_module<ConfigManager>();
	this->src_manager	= register_core_module<ResourceManager>();
	this->render		= register_core_module<Render>();
	this->input			= register_core_module<Input>();
	this->shader_proc	= register_core_module<ShaderProcessor>();
	this->manager		= register_core_module<Manager>();

	for (auto* m : core_modules) {
		m->initiliaze();
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
	for (auto p : mem::allocated_memory) {
		if (p.adress != this) {
			throw utils::format("Memory is not deleted! Adress: %p, Typename: %s", p.adress, p.type_name.data());
		}
	}
	auto allocated_mem		= mem::total_allocated;
	
	auto allocated_mem_bits = BYTE_TO_BIT	(allocated_mem);
	auto allocated_mem_kb	= BYTE_TO_KB	(allocated_mem);
	auto allocated_mem_mb	= BYTE_TO_MB	(allocated_mem);

	this->printf(
		"Total allocated memory: %i Bits => %i Bytes => %i KB => %i MB",
		LogType::Warning,
		allocated_mem_bits, allocated_mem, allocated_mem_kb, allocated_mem_mb
	);
}

void Core::print(const cstr& message, LogType type)
{
	utils::print_at_console(message, type);
}

void Core::fatal_error(const cstr& message)
{
	core->printf("Fatal error! Message: %s", LogType::Error, message.data());
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR, "Fatal error corrupted", message.data(), nullptr
	);
	exit(EXIT_FAILURE);
}