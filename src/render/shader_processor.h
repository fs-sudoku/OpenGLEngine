#pragma once
#include <scripting\scriptable_object.h>

class ShaderProcessor : IScriptableObject
{
public:
	ShaderProcessor();
	cstr get_completed_shader(const cstr& code, bool vertex);
};