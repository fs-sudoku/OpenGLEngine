#pragma once
#include <core\core.h>

#include "updatable_object.h"

class Manager : ICoreModule
{
public:
	std::vector<IUpdatableObject*> updatable_objects;
protected:
	friend class Core;
	void initiliaze() override;
	void process_update() override;
	void destroy() override;
};