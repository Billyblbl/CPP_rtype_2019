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

class Renderer : public ECS::TSystem<std::unique_ptr<sf::RenderWindow>, sf::Sprite>{
	public:

		using UniqueWindow = std::unique_ptr<sf::RenderWindow>;

		template<typename... Components>
		Renderer(Scheduler &scheduler, ECS::TComponentTable<Components> &... tables):
			ECS::TSystem<UniqueWindow, sf::Sprite>(scheduler, tables...)
		{}
	private :
		void    onLoad() override;
};
#endif /* !RENDERER_HPP_ */
