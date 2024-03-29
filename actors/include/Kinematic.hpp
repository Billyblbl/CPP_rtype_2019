/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Kinematic
*/

#ifndef KINEMATIC_HPP_
#define KINEMATIC_HPP_

#include "TSystem.hpp"
#include "Controller.hpp"
#include "Component.hpp"
#include "Timer.hpp"
#include "Speed.hpp"

class Kinematic : public ECS::TSystem<
	Controller,
	Position,
	Timer,
	Speed
> {
	public:

		template<typename... Components>
		Kinematic(Scheduler &scheduler, ECS::TComponentTable<Components> &... tables):
			ECS::TSystem<Components...>(scheduler, tables...)
		{}

	protected:
	private:
		void	onLoad() override;
};

#endif /* !KINEMATIC_HPP_ */
