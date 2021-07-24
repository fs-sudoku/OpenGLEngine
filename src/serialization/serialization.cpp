#include <serialization\serialization.h>

#include <core\core.h>
#include <engine\config_manager.h>

ISerializableObject::ISerializableObject(const cstr& path) : path(path)
{ 
	core->cfg_manager->get_serializable_objects().push_back(this);
}

void ISerializableObject::load_config()
{
	const auto& converted_path = RESOURCE_PATH(path.data());
	auto& all_cfg = core->cfg_manager->get_all_configs();

	VERIFY(utils::find_in_map(all_cfg, converted_path) == true);

	this->self_config = &(all_cfg.at(converted_path));

	VERIFY(this->self_config != nullptr);
}

void ISerializableObject::save_data(Json* config)
{
	// TODO
}

void ISerializableObject::read_data(const Json* config) const
{
	// TODO
}