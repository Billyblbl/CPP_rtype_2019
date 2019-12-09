/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Manifest
*/

#ifndef MANIFEST_HPP_
#define MANIFEST_HPP_

#include <string>
#include <unordered_map>
#include "Instance.hpp"
#include "TAsset.hpp"
#include "TEvent.hpp"

#if defined(_WIN32)
  // MS Windows DLLs (*.dll)
  #define PLUGIN_VISIBLE extern "C" __declspec(dllexport)
#else
  // Unix-like Shared Object (.so) operating systems and GCC.
  #define PLUGIN_VISIBLE extern "C" __attribute__((visibility("default")))
#endif

template<typename BuilderT>
using BuilderEntry = std::pair<std::string_view, BuilderT>;

template<typename Component, bool JSONParsable = false>
constexpr BuilderEntry<Instance::ComponentBuilder>	makeComponentEntry(const std::string_view &identifier)
{
	return std::make_pair(identifier, [](decltype(Instance::components) &manager, ECS::EntityID entity, const JSONValue &params){
		if (!manager->hasTable<Component>())
			manager->addTable<Component>();
		if constexpr (JSONParsable)
			manager->getTable<Component>().emplace(entity, params);
		else
			manager->getTable<Component>().emplace(entity);
	});
}

template<typename Asset>
constexpr BuilderEntry<Instance::ComponentBuilder>	makeAssetEntry(const std::string_view &identifier)
{
	using Component = ECS::TAsset<Asset>;
	return std::make_pair(identifier, [](decltype(Instance::components) &manager, ECS::EntityID entity, const JSONValue &params){
		if (!manager->hasTable<Component>())
			manager->addTable<Component>();
		manager->getTable<Component>().emplace(entity, params.get<JSONValue::String>());
	});
}

template<typename Event>
constexpr BuilderEntry<Instance::ComponentBuilder>	makeEventEntry(const std::string_view &identifier)
{
	using Component = TEvent<Event>;
	return std::make_pair(identifier, [](decltype(Instance::components) &manager, ECS::EntityID entity, const JSONValue &params){
		if (!manager->hasTable<Component>())
			manager->addTable<Component>();
		manager->getTable<Component>().emplace(entity);
		for (auto i = 0; i < params.get<JSONValue::Numberi>(); ++i) {
			manager->getTable<Component>()[entity]->enqueue(Event{});
		}
	});
}

template<typename System, bool JSONParsable = false>
constexpr BuilderEntry<Instance::SystemBuilder>	makeSystemEntry(const std::string_view &identifier)
{
	return std::make_pair(identifier, [](decltype(Instance::systems) &manager, const JSONValue &params){
		if constexpr (JSONParsable)
			manager->addSystem<System>(params);
		else
			manager->addSystem<System>();
	});
}

template<typename BuilderT>
using BuilderTable = BuilderEntry<BuilderT>[];

// PLUGIN_VISIBLE Instance::ComponentBuilder	getComponentBuilder(const std::string &type);
// PLUGIN_VISIBLE Instance::SystemBuilder		getSystemBuilder(const std::string &type);

// Can't use extern "C" in a template (because obviously C doesn't know how template
// linkage works so here comes macros template hell

///
///@brief Define all components exposable as R-Engine Plugin
///
///
#define EXPOSABLE_COMPONENTS constexpr BuilderTable<Instance::ComponentBuilder>	ComponentBuilders =

///
///@brief Expose all previously defined exposable component
///
///
#define EXPOSE_COMPONENTS PLUGIN_VISIBLE Instance::ComponentBuilder	getComponentBuilder(const std::string &type)					\
{																											\
	auto it = std::find_if(std::begin(ComponentBuilders), std::end(ComponentBuilders), [&](auto entry){		\
		return entry.first == type;																			\
	});																										\
	if (it != std::end(ComponentBuilders))																	\
		return it->second;																					\
	else																									\
		throw std::runtime_error(std::string(__func__) + " : Component type not found : " + type);			\
};																											\
\

///
///@brief Define all systems exposable as R-Engine Plugin
///
///
#define EXPOSABLE_SYSTEMS constexpr BuilderTable<Instance::SystemBuilder>		SystemBuilders =

///
///@brief Expose all previously defined exposable systems
///
///
#define EXPOSE_SYSTEMS PLUGIN_VISIBLE Instance::SystemBuilder		getSystemBuilder(const std::string &type)	\
{																												\
	auto it = std::find_if(std::begin(SystemBuilders), std::end(SystemBuilders), [&](auto entry){				\
		return entry.first == type;																				\
	});																											\
	if (it != std::end(SystemBuilders))																			\
		return it->second;																						\
	else																										\
		throw std::runtime_error(std::string(__func__) + " : Component type not found : " + type);				\
}																												\

#endif /* !MANIFEST_HPP_ */

