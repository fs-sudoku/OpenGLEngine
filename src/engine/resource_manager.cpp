#include <engine\resource_manager.h>

#include <filesystem>

ResourceManager::ResourceManager() : IScriptableObject("scripts/resource_manager.lua")
{ }

std::vector<cstr> ResourceManager::convert_config_path(const cstr& path)
{
	return { path };
}

void ResourceManager::initiliaze()
{

}

void ResourceManager::destroy()
{

}