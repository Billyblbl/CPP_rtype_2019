/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Inputs
*/

#ifndef INPUTS_HPP_
#define INPUTS_HPP_

#include "TSystem.hpp"
#include "SFML/Window.hpp"
#include "Component.hpp"
#include "Controller.hpp"

class Inputs : public ECS::TSystem<
	TEvent<sf::Event>,
	TEvent<Controller::BeamFire>,
	Controller
> {
	public:

		using BeamFire = Controller::BeamFire;

		template<typename... Components>
		Inputs(Scheduler &scheduler, ECS::TComponentTable<Components> &... tables):
			ECS::TSystem<Components...>(scheduler, tables...)
		{}

	protected:
	private:
		void	onLoad() override;
};

#endif /* !INPUTS_HPP_ */
