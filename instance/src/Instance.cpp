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
#include "IComponentBuilder.hpp"

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

void	Instance::loadPlugins(const JSONValue::Array &plugs)
{
	try {
		for (auto &plugin : plugs) {
			plugins->load(plugin.get<JSONValue::String>());
		}
	} catch(const std::exception& e) {
		throw std::runtime_error(std::string("Plugin failure : ") + e.what());
	}
}

void	Instance::loadEntities(const JSONValue::Array &ents)
{
	try {
		for (auto &entity : ents) {
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
		}
		std::cout << "loaded " << entities->getPopSize() << " entities" << std::endl;
	} catch(const std::exception& e) {
		throw std::runtime_error(std::string("Entity failure : ") + e.what());
	}
}

void	Instance::loadSystems(const JSONValue::Array &syss)
{
	try {
		for (auto &system : syss) {
			auto			&srcKey = system["source"].get<JSONValue::String>();
			auto			&systemSource = plugins[srcKey];
			SystemBuilder	build = systemSource.call<SystemBuilder(const std::string&)>(
				"getSystemBuilder",
				system["type"].get<JSONValue::String>()
			);
			build(systems, system["params"]);
		}
		systems->reload();
	} catch(const std::exception& e) {
		throw std::runtime_error(std::string("Systems failure : ") + e.what());
	}
}

