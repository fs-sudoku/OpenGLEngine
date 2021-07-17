#pragma once
#include <core\core_module.h>
#include <base_types\base_types.h>
#include <scripting\scriptable_object.h>

class ResourceManager : ICoreModule, IScriptableObject
{
public:
	ResourceManager();
public:
	std::vector<cstr> convert_config_path(const cstr& path);
private:
	friend class Core;
	void initiliaze()	override;
	void destroy()		override;
};