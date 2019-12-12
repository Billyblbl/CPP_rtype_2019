/*
** EPITECH PROJECT, 2019
** rype
** File description:
** Game Instance object
*/

#ifndef INSTANCE_HPP_
#define INSTANCE_HPP_

#include "Scheduler.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "EventMediator.hpp"
#include "EntityPool.hpp"
#include "TGuarded.hpp"
#include "JSONValue.hpp"
#include "PluginManager.hpp"

///
///@brief Game instance object
///
///
class Instance {
	public:

		Instance();

		Instance(const std::string &path);

		void	load(const std::string &path);
		void	reload(const std::string &path);
		void	clear();
		using ID = uint64_t;

		TGuarded<ECS::EntityPool>		entities;
		TGuarded<ECS::ComponentManager>	components;
		TGuarded<Scheduler>				scheduler;
		TGuarded<ECS::SystemManager>	systems;
		TGuarded<PluginManager>			plugins;

		using ComponentBuilder = void(*)(decltype(components) &, ECS::EntityID, const JSONValue &);
		using SystemBuilder = void(*)(decltype(systems) &, const JSONValue &);

		ID	getID() const;

	protected:
	private:

		void	loadPlugins(const JSONValue::Array &plugs);
		void	loadEntities(const JSONValue::Array &ents);
		void	loadSystems(const JSONValue::Array &syss);
		ID			_id;

		static ID	nextID;
};

#endif /* !INSTANCE_HPP_ */
