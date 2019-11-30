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

		Instance();

		using ID = uint64_t;

		TGuarded<ECS::EntityPool>		entities;
		TGuarded<ECS::ComponentManager>	components;
		TGuarded<Scheduler>				scheduler;
		TGuarded<ECS::SystemManager>	systems;

		ID	getID() const;

	protected:
	private:
		ID			_id;

		static ID	nextID;
};

#endif /* !INSTANCE_HPP_ */
