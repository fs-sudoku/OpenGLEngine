#pragma once
#include <scripting\scriptable_object.h>

class ShaderProcessor : IScriptableObject
{
public:
	ShaderProcessor();
	std::tuple<cstr, cstr> get_completed_shader(const cstr& path);
};