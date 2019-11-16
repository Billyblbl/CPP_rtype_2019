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

class Instance {
	public:

		Scheduler			scheduler;
		ComponentManager	components;
		SystemManager		systems;

	protected:
	private:
};

#endif /* !INSTANCE_HPP_ */
