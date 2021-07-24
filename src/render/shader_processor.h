#pragma once
#include <core\core_module.h>
#include <scripting\scriptable_module.h>


class ShaderProcessor : ICoreModule, IScriptableModule
{
public:
	ShaderProcessor();
	std::tuple<cstr, cstr>	get_completed_shader(const cstr& path);
	std::vector<uint>		get_base_locations(uint id);
private:
	friend class Shader;
	friend class Render;
	friend class Core;
private:
	void initiliaze() override;
	std::vector<class Shader*> shaders;
};