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

///
///@brief Game instance object
///
///
class Instance {
	public:

		Instance() = default;

		TGuarded<ECS::EntityPool>		entities;
		TGuarded<ECS::ComponentManager>	components;
		TGuarded<ECS::SystemManager>	systems;
		TGuarded<Scheduler>				scheduler;
		// TGuarded<EventMediator>			events;

	protected:
	private:
};

#endif /* !INSTANCE_HPP_ */
