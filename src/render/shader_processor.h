#pragma once
#include <scripting\scriptable_object.h>

class ShaderProcessor : IScriptableObject
{
public:
	ShaderProcessor();
	std::tuple<cstr, cstr>	get_completed_shader(const cstr& path);
	std::vector<uint>		get_base_locations(uint id);
private:
	friend class Shader;
	friend class Render;
	std::vector<class Shader*> shaders;
};