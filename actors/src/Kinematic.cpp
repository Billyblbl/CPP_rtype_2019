/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Kinematic
*/

#include "Kinematic.hpp"

void	Kinematic::onLoad()
{
	declareTask<const Controller, const Timer, const Speed, Position>([](auto &controllers, auto &timers, auto &speeds, auto &positions){
		for (auto &controller : controllers) {
			// std::cout << __func__ << ' ' << controller->direction.x << ' ' << controller->direction.y << std::endl;
			// std::cout << "old Position = " << positions[controller.getID()]->value.x << "," << positions[controller.getID()]->value.y << std::endl;
			auto	speed = speeds[controller.getID()]->value;
			// std::cout << "speed = " << speed << std::endl;
			auto	deltaT = (*timers.begin())->deltaT.count();
			// std::cout << typeid(deltaT).name() << " deltaT = " << deltaT << std::endl;
			auto distance = speed * deltaT / 1000000;
			positions[controller.getID()]->value += controller->direction * distance;
			// std::cout << "new Position = " << positions[controller.getID()]->value.x << "," << positions[controller.getID()]->value.y << std::endl;
		}
	});
}
