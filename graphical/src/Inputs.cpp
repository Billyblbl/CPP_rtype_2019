/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Inputs
*/

#include "Inputs.hpp"
#include "Controller.hpp"

void	Inputs::onLoad()
{

	declareTask<Controller>([](auto &controllers){
		for (auto &controller : controllers) {
			// controller->direction = {0.f, 0.f};
			std::cout << "controller = " << controller->direction.x << ' ' << controller->direction.y << std::endl;
		}
	});

	on<sf::Event, Controller>([](auto &event, auto source, auto &controllers){
		for (auto &controller : controllers) {
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Z : controller->direction.y = -1.f;
					break;
				case sf::Keyboard::Q : controller->direction.x = -1.f;
					break;
				case sf::Keyboard::S : controller->direction.y = 1.f;
					break;
				case sf::Keyboard::D : controller->direction.x = 1.f;
					break;
				case sf::Keyboard::Space : {
					controller->charging = true;
					//TODO make this depend on a delta timer
					controller->beamCharge += 5.f;
				}
					break;
				default:
					break;
				}
			}
		}
	});

	declareTask<TEvent<BeamFire>>([](auto &fireEvents){
		for (auto &queue : fireEvents) {
			queue->clear();
		}
	});

	on<sf::Event, Controller, TEvent<BeamFire>>([](auto &event, auto source, auto &controllers, auto &fireEvents)
	{
		for (auto &controller : controllers) {
			fireEvents[controller.getID()]->clear();
			if (event.type == sf::Event::KeyReleased) {
				std::cout << "released" << std::endl;
				switch (event.key.code) {
				case sf::Keyboard::Z :
				case sf::Keyboard::S :
					std::cout << "reset y" << std::endl;
					controller->direction.y = 0.f;
					break;
				case sf::Keyboard::Q :
				case sf::Keyboard::D :
					std::cout << "reset x" << std::endl;
					controller->direction.x = 0.f;
					break;
				case sf::Keyboard::Space : {
					controller->charging = false;
					fireEvents[controller.getID()]->enqueue(BeamFire{controller->beamCharge});
					controller->beamCharge = 0.f;
				}
					break;
				default:
					break;
				}
			}
		}
	});

}