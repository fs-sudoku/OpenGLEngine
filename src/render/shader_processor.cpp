#include <render\shader_processor.h>

ShaderProcessor::ShaderProcessor() : IScriptableObject("scripts/shader_processor.lua")
{ 
	script->call_init();
}

std::tuple<cstr, cstr> ShaderProcessor::get_completed_shader(const cstr& path)
{
	auto result = script->call_method<luabridge::LuaRef>("process_shader", path);
	cstr first = result[1], second = result[2];
	return std::tuple<cstr, cstr>(first, second);
}

std::vector<uint> ShaderProcessor::get_base_locations(uint id)
{
	std::vector<uint> result;
	auto lua_ref = script->call_method<luabridge::LuaRef>("get_base_locations", id);
	for (size_t i = 0; i < lua_ref.length(); i++) {
		result.push_back(lua_ref[i + 1].cast<uint>());
	}
	return result;
}
