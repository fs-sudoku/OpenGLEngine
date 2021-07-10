#pragma once
#include <core\core.h>
#include <scripting\scriptable_object.h>

#include "updatable_object.h"

class Manager : ICoreModule, IScriptableObject
{
public:
	Manager();
public:
	std::vector<IUpdatableObject*> updatable_objects;
protected:
	friend class Core;
	void initiliaze() override;
	void process_update() override;
	void destroy() override;
};