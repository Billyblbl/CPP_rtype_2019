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
#include "TAsset.hpp"

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

	// // random test task
	// declareTask<Rotation>([](auto &rotations){
	// 	for(auto &rotation : rotations) {
	// 		rotation->value += 0.3;
	// 	}
	// });

	//draw task
	declareTask<UniqueWindow, const sf::Sprite, TEvent<sf::Event>>([](auto &windows, auto &sprites, auto &events){
		for(auto &window : windows) {
			auto	entity = window.getID();
			auto	&win = *window;
			if (win.handle->isOpen()) {
				win.handle->setActive(true);
				sf::Event event = {};
				events[entity]->clear();
				while (win.handle->pollEvent(event)) {
					if (event.type == sf::Event::Closed ||
						(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
						win.handle->close();
					else
						events[entity]->enqueue(std::move(event));
				}
				win.handle->clear(/* sf::Color::Black */);
				for (auto &sprite : sprites) {
					win.handle->draw(*sprite);
				}
				win.handle->display();
				win.handle->setActive(false);
			}
		}
	});

	on<TextureChanged, sf::Sprite, const ECS::TAsset<CachedTexture>>([](auto &events, auto source, auto &sprites, auto &textures) {
		sprites[source]->setTexture((*textures[source])->texture, true);
		auto	[_1, _2, width, height] = sprites[source]->getLocalBounds();
		sprites[source]->setOrigin(width / 2.f, height / 2.f);
	});

}