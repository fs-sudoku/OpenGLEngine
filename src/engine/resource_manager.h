#pragma once
#include <core\core_module.h>

class ResourceManager : ICoreModule
{
private:
	friend class Core;
	void initiliaze() override;
	void destroy() override;
};