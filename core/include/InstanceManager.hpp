/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** core system - instance manager
*/

#ifndef INSTANCEMANAGER_HPP_
#define INSTANCEMANAGER_HPP_

#include "TSystem.hpp"
#include "InstanceCalls.hpp"
#include "Timer.hpp"

class InstanceManager : public ECS::TSystem<
	TEvent<InstanceCalls::Type>,
	Timer
> {
	public:

		template<typename... Components>
		InstanceManager(Scheduler &scheduler, ECS::TComponentTable<Components> &... tables):
			ECS::TSystem<Components...>(scheduler, tables...)
		{}

	protected:
	private:
		void	onLoad() override;
};

#endif /* !INSTANCEMANAGER_HPP_ */
