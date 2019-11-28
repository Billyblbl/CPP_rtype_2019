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

Instance::Instance():
	systems{*scheduler}
{}

Instance::Instance(const std::string &path):
	Instance()
{
	load(path);
}

void	Instance::load(const std::string &path)
{
	try {
		auto			level = AssetCache::getGlobalCache().load<CachedJSON>(path);
		auto			guard = *scheduler;
		loadPlugins(level->value[std::string("plugins")]);
		loadEntities(level->value[std::string("entities")]);
		loadSystems(level->value[std::string("systems")]);
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

void	Instance::loadPlugins(const JSONValue::Array &plugs)
{
	for (auto &plugin : plugs) {
		try {
			plugins->load(plugin.get<JSONValue::String>());
		} catch(const std::exception& e) {
			std::cerr << "Plugin load failure : " << e.what();
		}
	}
}

void	Instance::loadEntities(const JSONValue::Array &ents)
{
	for (auto &entity : ents) {
		try {
			auto newEnt = entities->takeID();
			for (auto &component : entity["components"]) {
				auto				&srcKey = component["source"].get<JSONValue::String>();
				auto				&componentSource = plugins[srcKey];
				ComponentBuilder	build = componentSource.call<ComponentBuilder(const std::string&)>(
					"getComponentBuilder",
					component["type"].get<JSONValue::String>()
				);
				build(components, newEnt, component["params"]);
			}
		} catch(const std::exception& e) {
			std::cerr << "Entity load failure : " << e.what();
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
			std::cerr << "System load failure : " << e.what();
		}
	}
	systems->reload();
}

