#pragma once
#include <base_types\object.h>
#include <base_types\base_types.h>

#include <core\core_module.h>

#include <main.h>

extern Core* core;

class Core : ICoreModule
{
public:
	class Render* render			= nullptr;
	class LuaManager* lua_manager	= nullptr;
	class Manager* manager			= nullptr;

	bool is_editor					= false;
	bool is_debug					= false;
public:
	Core(bool is_editor, bool is_debug);
public:
	static void print(const cstr message);
	static void fatal_error(const cstr message);
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
	std::vector<ICoreModule*> core_modules;
private:
	template<typename T = ICoreModule>
	inline T* register_core_module()
	{
		T* result = mem::alloc<T>();

		ICoreModule* as_module = dynamic_cast<ICoreModule*>(result);

		this->core_modules.push_back(as_module);
		as_module->initiliaze();

		return result;
	}
};