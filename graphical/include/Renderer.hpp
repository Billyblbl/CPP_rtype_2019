/*
** EPITECH PROJECT, 2019
** R-type
** File description:
** Renderer system
*/

#ifndef RENDERER_HPP_
#define RENDERER_HPP_
#include <SFML/Graphics.hpp>
#include <memory>
#include "TComponentTable.hpp"
#include "TSystem.hpp"
#include "Component.hpp"

class Renderer : public ECS::TSystem<
	std::unique_ptr<sf::RenderWindow>,
	sf::Sprite,
	Scale,
	Position,
	Rotation
> {
	public:

		using UniqueWindow = std::unique_ptr<sf::RenderWindow>;

		template<typename... Components>
		Renderer(Scheduler &scheduler, ECS::TComponentTable<Components> &... tables):
			ECS::TSystem<Components...>(scheduler, tables...)
		{}
	private :
		void    onLoad() override;
};
#endif /* !RENDERER_HPP_ */
