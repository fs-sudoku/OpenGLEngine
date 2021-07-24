#pragma once
#include <nlohmann\json.hpp>

#include <base_types\object.h>

using Json = nlohmann::basic_json<>;

class ISerializableObject : IObject
{
public:
	ISerializableObject(const cstr& path);
protected:
	friend class ConfigManager;
	cstr path = nullptr;
	Json* self_config = nullptr;
	void load_config();
	virtual void save_data(Json* config);
	virtual void read_data(const Json* config) const;
};