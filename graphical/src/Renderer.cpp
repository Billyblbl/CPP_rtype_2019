/*
** EPITECH PROJECT, 2019
** R-type
** File description:
** Renderer method declaration
*/

#include <iostream>
#include "Renderer.hpp"
#include "Component.hpp"

void    Renderer::onLoad() {
	//draw task
	declareTask<UniqueWindow,const sf::Sprite>([](auto &windows, auto &sprites){
		for(auto &window : windows) {
			for (auto &sprite : sprites) (*window)->draw(*sprite);
			(*window)->display();
		}
	});
	//rescale task
	declareTask<sf::Sprite, const Scale>([](auto &sprites, auto &scales){
		for(auto &sprite : sprites) {
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
	declareTask<sf::Sprite, Rotation>([](auto &sprites, auto &rotations){
		for(auto &sprite : sprites) {
			sprite->setRotation(rotations[sprite.getID()]->value);
		}
	});
}