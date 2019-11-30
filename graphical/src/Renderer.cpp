/*
** EPITECH PROJECT, 2019
** R-type
** File description:
** Renderer method declaration
*/

// #include <iostream>
#include <SFML/Graphics.hpp>

#include "Renderer.hpp"
#include "Component.hpp"

void    Renderer::onLoad() {

	//rescale task
	declareTask<sf::Sprite, const Scale>([](auto &sprites, auto &scales){
		for(auto &sprite : sprites) {
			// std::cout << "sprite " << &sprite << std::endl;
			sprite->setScale(scales[sprite.getID()]->value.x, scales[sprite.getID()]->value.y);
		}
	});

	//position task
	declareTask<sf::Sprite, const Position>([](auto &sprites, auto &positions){
		for(auto &sprite : sprites){
			sprite->setPosition(positions[sprite.getID()]->value.x, positions[sprite.getID()]->value.y);
		}
	});

	//rotation task
	declareTask<sf::Sprite, const Rotation>([](auto &sprites, auto &rotations){
		for(auto &sprite : sprites) {
			sprite->setRotation(rotations[sprite.getID()]->value);
		}
	});

	// random test task
	declareTask<Rotation>([](auto &rotations){
		for(auto &rotation : rotations) {
			rotation->value += 0.3;
		}
	});

	//draw task
	declareTask<UniqueWindow, const sf::Sprite>([](auto &windows, auto &sprites){
		for(auto &window : windows) {
			auto	&win = *window;
			if (win->isOpen()) {
				sf::Event event = {};
				while (win->pollEvent(event)) {
					if (event.type == sf::Event::Closed ||
						(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
						win->close();
				}
				win->clear(sf::Color::Black);
				for (auto &sprite : sprites) {
					win->draw(*sprite);
				}
				win->display();
			}
		}
	});
}