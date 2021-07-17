#pragma once
#include <base_types\object.h>
#include <memory\memory.h>

#include <utils\utils.h>

class ICoreModule : IObject
{
protected:	
	friend class Core;
	virtual void initiliaze() {};
	virtual void process_update() {};
	virtual void destroy() {};
};