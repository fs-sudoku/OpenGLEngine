#pragma once
#include <base_types\base_types.h>
#include <base_types\object.h>

#include <utils\utils.h>

class IUpdatableObject : IObject
{
public:
	IUpdatableObject();
	~IUpdatableObject();
protected:
	friend class Manager;
	virtual void update() = 0;
};