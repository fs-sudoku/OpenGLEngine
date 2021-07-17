#pragma once
#include <base_types\object.h>
#include <base_types\base_types.h>

#include <serialization\serialization.h>
#include <core\core_module.h>

#include <main.h>

extern Core* core;

constexpr bool is_editor	= static_cast<bool>(IS_EDITOR);
constexpr bool is_debug		= static_cast<bool>(IS_DEBUG);

class Core : ICoreModule
{
public:
	class Render* render				= nullptr;
	class LuaManager* lua_manager		= nullptr;
	class Manager* manager				= nullptr;
	class ShaderProcessor* shader_proc	= nullptr;
	class ResourceManager* src_manager	= nullptr;
public:
	static void print(const cstr& message, LogType type = LogType::Info);
	static void fatal_error(const cstr& message);
public:
	REGISTER_READ_ONLY_PROPERTY(Json, main_config);
protected:
	friend class Render;
	friend int main(int argc, char* argv[]);
protected:
	void initiliaze() override;
	void process_update() override;
	void destroy() override;
private:
	void start_update_in_render();
	void register_std_exception(const std::exception& excp);
private:
	Json main_config;
private:
	std::vector<ICoreModule*> core_modules;
	std::thread start_up_thread;
private:
	template<typename T = ICoreModule>
	_NODISCARD T* register_core_module() {
		static_assert(std::is_base_of<ICoreModule, T>::value, "T is not ICoreModule");

		T* result = mem::alloc<T>();
		ICoreModule* as_module = dynamic_cast<ICoreModule*>(result);
		this->core_modules.push_back(as_module);
		return result;
	}
};