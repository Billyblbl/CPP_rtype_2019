/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** PluginManager
*/

#include "PluginManager.hpp"
#include "AssetCache.hpp"

Plugin			&PluginManager::load(const std::string &path)
{
	return *(_plugins[path] = AssetCache::getGlobalCache().load<Plugin>(path));
}

void			PluginManager::unload(const std::string &path)
{
	_plugins.erase(path);
}

void			PluginManager::clear()
{
	_plugins.clear();
}

Plugin			&PluginManager::operator[](const std::string &key)
{
	return	*_plugins.at(key);
}

const Plugin	&PluginManager::operator[](const std::string &key) const
{
	return *_plugins.at(key);
}
