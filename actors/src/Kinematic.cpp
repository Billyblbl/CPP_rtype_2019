/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Kinematic
*/

#include "Kinematic.hpp"

void	Kinematic::onLoad()
{
	declareTask<const Controller, Position>([](auto &controllers, auto &positions){
		for (auto &controller : controllers) {
			// std::cout << __func__ << ' ' << controller->direction.x << ' ' << controller->direction.y << std::endl;
			//TODO make this depend on a delta timer
			positions[controller.getID()]->value += controller->direction;
		}
	});
}
