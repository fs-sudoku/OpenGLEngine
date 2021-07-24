#pragma once
#include <core\core.h>
#include <scripting\scriptable_module.h>

#include "updatable_object.h"

class Manager : ICoreModule
{
public:
	Manager();
public:
	REGISTER_READ_ONLY_PROPERTY(auto&, updatable_objects);
	REGISTER_PROPERTY(class Actor*, actor);
protected:
	friend class Core;
	void initiliaze() override;
	void process_update() override;
	void destroy() override;
private:
	std::vector<IUpdatableObject*> updatable_objects;
	class Actor* actor = nullptr;
	class Camera* camera = nullptr;
};