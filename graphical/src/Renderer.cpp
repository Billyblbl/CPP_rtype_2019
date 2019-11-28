/*
** EPITECH PROJECT, 2019
** R-type
** File description:
** Renderer method declaration
*/

#include <iostream>
#include "Renderer.hpp"

void    Renderer::onLoad() {
	declareTask<UniqueWindow, sf::Sprite>([](auto &windows, auto &sprites){
		for(auto &window: windows) {
			for (auto &sprite : sprites) (*window)->draw(*sprite);
			(*window)->display();
		}
	});
}