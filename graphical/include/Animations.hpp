/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Animations
*/

#ifndef ANIMATIONS_HPP_
#define ANIMATIONS_HPP_

#include "TSystem.hpp"
#include "Animations.hpp"
#include "Animator.hpp"
#include "SFML/Graphics.hpp"

class Animations : public ECS::TSystem<
	sf::Sprite,
	Animator,
	Timer
>{
	public:

		template<typename... Components>
		Animations(Scheduler &scheduler, ECS::TComponentTable<Components> &... tables):
			ECS::TSystem<Components...>(scheduler, tables...)
		{}

	protected:
	private:

		void	onLoad();
};

#endif /* !ANIMATIONS_HPP_ */
