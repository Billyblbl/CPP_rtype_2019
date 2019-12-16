/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Game instance object definition
*/

#include <iostream>
#include <string>
#include "Instance.hpp"
#include "AssetCache.hpp"
#include "JSONValue.hpp"
#include "CachedJSON.hpp"

Instance::ID	Instance::nextID = 0;

Instance::Instance():
	systems{*scheduler, *components},
	_id{nextID++}
{}

Instance::Instance(const std::string &path):
	Instance()
{
	load(path);
}

void	Instance::load(const std::string &path)
{
	try {
		auto		level = AssetCache::getGlobalCache().load<CachedJSON>(path);
		auto		guard = *scheduler;
		const auto	&pluginsJSON = level->value[std::string("plugins")];
		const auto	&entitiesJSON = level->value[std::string("entities")];
		const auto	&systemsJSON = level->value[std::string("systems")];
		if (!pluginsJSON.isNull())
			loadPlugins(pluginsJSON);
		if (!entitiesJSON.isNull())
			loadEntities(entitiesJSON);
		if (!systemsJSON.isNull())
			loadSystems(systemsJSON);
	} catch(const std::exception& e) {
		throw std::runtime_error(std::string("Load failure : ") + e.what());
	}
}

void	Instance::reload(const std::string &path)
{
	//some sort of clear but keeping some specified stuff in the instance
	clear();//tmp
	load(path);
}

void	Instance::clear()
{
	//clear all
}

bool	Instance::poll()
{
	TaskExecutor	task = nullptr;
	{
		auto	lockedSched = *scheduler;
		if (lockedSched->hasAvailableTask())
			task = lockedSched->takeTask();
		else if (!lockedSched->hasPendingTask())
			return false;
	}
	if (task != nullptr) {
		try {
			(*task)();
		} catch(const std::exception& e) {
			std::cerr << "Task Failed" << e.what() << '\n';
		}
		scheduler->reportTask(task);
	}
	return true;
}

void	Instance::loadPlugins(const JSONValue::Array &plugs)
{
	for (auto &plugin : plugs) {
		try {
			plugins->load(plugin.get<JSONValue::String>());
		} catch(const std::exception& e) {
			std::cerr << "Plugin load failure : " << e.what() << "\r\n";
		}
	}
}

void	Instance::loadEntities(const JSONValue::Array &ents)
{
	for (auto &entity : ents) {
		auto newEnt = entities->takeID();
		try {
			for (auto &component : entity["components"]) {
				try {
					auto				&srcKey = component["source"].get<JSONValue::String>();
					auto				&componentSource = plugins[srcKey];
					ComponentBuilder	build = componentSource.call<ComponentBuilder(const std::string&)>(
						"getComponentBuilder",
						component["type"].get<JSONValue::String>()
					);
					build(components, newEnt, component["params"]);
				} catch(const std::exception &e) {
					std::cerr << "Component load failure : " << component["type"].get<JSONValue::String>() << ' ' << e.what() << "\r\n";
				}
			}
		} catch(const std::exception& e) {
			std::cerr << "Entity load failure : " << e.what() << "\r\n";
			entities->returnID(newEnt);
		}
	}
	std::cout << "loaded " << entities->getPopSize() << " entities" << std::endl;
}

void	Instance::loadSystems(const JSONValue::Array &syss)
{
	for (auto &system : syss) {
		try {
			auto			&srcKey = system["source"].get<JSONValue::String>();
			auto			&systemSource = plugins[srcKey];
			SystemBuilder	build = systemSource.call<SystemBuilder(const std::string&)>(
				"getSystemBuilder",
				system["type"].get<JSONValue::String>()
			);
			build(systems, system["params"]);
		} catch(const std::exception& e) {
			std::cerr << "System load failure : " << e.what() << "\r\n";
		}
	}
	systems->reload();
}

Instance::ID	Instance::getID() const
{
	return _id;
}

const std::string &Instance::getLevel() const
{
	return _currentLevel;
}
