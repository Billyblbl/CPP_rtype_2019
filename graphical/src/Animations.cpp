/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Animations
*/

#include "Animations.hpp"

void	Animations::onLoad()
{
	declareTask<Animator, Timer>([](auto &animators, auto &timers){
		for (auto &animator : animators) {
			animator->setFrame((*timers.begin())->now);
		}
	});

	declareTask<sf::Sprite, const Animator>([](auto &sprites, auto &animators){
		for (auto &animator : animators) {
			auto	&sprite = sprites[animator.getID()];
			sprite->setTextureRect(animator->getCurrentFrame());
			auto	[_1, _2, width, height] = sprite->getLocalBounds();
			sprite->setOrigin(width / 2.f, height / 2.f);
		}
	});

}
