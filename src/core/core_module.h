#pragma once
#include <base_types\object.h>
#include <memory\memory.h>

#include <utils\utils.h>

class ICoreModule : IObject
{
protected:	
	friend class Core;
	virtual void initiliaze()		{ return; }
	virtual void process_update()	{ return; }
	virtual void destroy()			{ mem::free(this); }
};