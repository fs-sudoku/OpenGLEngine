#pragma once
#include "base_types.h"

class IObject
{
protected:
	virtual cstr get_name() const { return "base_object"; }
};