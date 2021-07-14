#include <render\shader_processor.h>

ShaderProcessor::ShaderProcessor() : IScriptableObject("scripts/shader_processor.lua")
{ }

cstr ShaderProcessor::get_completed_shader(const cstr& code, bool vertex)
{
	return script->call_method<cstr>("process_shader", code, vertex);
}