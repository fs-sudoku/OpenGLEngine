#pragma once
#include "base_types.h"

class IObject
{
protected:
	virtual cstr get_name() { return "base_object"; }
};