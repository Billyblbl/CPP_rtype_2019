/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** rtype client
*/
#include "Renderer.hpp"
#include "Instance.hpp"
#include "AssetCache.hpp"

#include <iostream>
struct CachedTexture {
	CachedTexture(const std::string &path)
	{
		texture.loadFromFile(path);
	}

	sf::Texture	texture;
};

int	main(int, char *av[])
{
	try
	{
		auto Texture = AssetCache::getGlobalCache().load<CachedTexture>(av[1]);
		Instance	instance;
		instance.components->addTable<Renderer::UniqueWindow>();
		instance.components->addTable<sf::Sprite>();
		instance.components->addTable<Scale>();
		instance.components->addTable<Position>();
		instance.components->addTable<Rotation>();
		auto &windowTable = instance.components->getTable<Renderer::UniqueWindow>();
		auto &spriteTable = instance.components->getTable<sf::Sprite>();
		auto &ScaleTable = instance.components->getTable<Scale>();
		auto &PositionTable = instance.components->getTable<Position>();
		auto &RotationTable = instance.components->getTable<Rotation>();
		instance.systems->addSystem<Renderer>(windowTable, spriteTable, ScaleTable, PositionTable ,RotationTable);
		auto WindowEntity = instance.entities->takeID();
		auto SpriteTest = instance.entities->takeID();
		instance.components->getTable<Renderer::UniqueWindow>().emplace(WindowEntity, std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), std::string("R-Engine")));
		std::cout << "gave window to " << WindowEntity << std::endl;
		instance.components->getTable<sf::Sprite>().emplace(SpriteTest, Texture->texture);
		std::cout << "gave sprite to " << SpriteTest << std::endl;
		instance.components->getTable<Scale>().emplace(SpriteTest, Scale{TVector2(2.f, 2.f)});
		std::cout << "gave Scale to " << SpriteTest << std::endl;
		instance.components->getTable<Position>().emplace(SpriteTest, Position{TVector2(2.f, 2.f)});
		std::cout << "gave Position to " << SpriteTest << std::endl;
		instance.components->getTable<Rotation>().emplace(SpriteTest, Rotation{2.f});
		std::cout << "gave Rotation to " << SpriteTest << std::endl;
		for (auto &window : instance.components->getTable<Renderer::UniqueWindow>()) {
			auto &win = *window;
			win->setFramerateLimit(140);
		}
		instance.systems->reload();
		while(true) {
			// std::cout << "frame" << std::endl;
			if (instance.scheduler->hasAvailableTask()) {
				auto &&task = instance.scheduler->takeTask();
				// std::cout << "task" << std::endl;
				try {
					(*task)();
				} catch(const std::exception& e) {
					std::cerr << e.what() << '\n';
				}
				// std::cout << "task execed" << std::endl;
				instance.scheduler->reportTask(task);
				// std::cout << "task reported" << std::endl;
			} else if (instance.scheduler->hasPendingTask())
			{
				// std::cout << "pending" << std::endl;
			}
		}
		return 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
}