#pragma once
#include <scripting\scriptable_module.h>

class ConfigManager : ICoreModule
{
public:
	REGISTER_READ_ONLY_PROPERTY(auto&, serializable_objects);
	REGISTER_READ_ONLY_PROPERTY(auto&, all_configs);
private:
	friend class Core;
	void initiliaze() override;

	void destroy() override;
private:
	std::vector<class ISerializableObject*> serializable_objects;
	std::map<cstr, Json> all_configs;
};