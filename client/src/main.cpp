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
		instance.components->getTable<Renderer::UniqueWindow>().emplace(WindowEntity, std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), std::string("R-Engine")));
		instance.components->getTable<sf::Sprite>().emplace(SpriteTest, Texture->texture);
		instance.components->getTable<Scale>().emplace(SpriteTest, Scale{TVector2(2.f, 2.f)});
		instance.components->getTable<Position>().emplace(SpriteTest, Position{TVector2(2.f, 2.f)});
		instance.components->getTable<Rotation>().emplace(SpriteTest, Rotation{2.f});
		instance.systems->reload();
		while(true) {
			// std::cout << "frame" << std::endl;
			if (instance.scheduler->hasAvailableTask()) {
				auto &&task = instance.scheduler->takeTask();
				std::cout << "task" << std::endl;
				(*task)();
				instance.scheduler->reportTask(task);
			} else if (instance.scheduler->hasPendingTask())
			{
				std::cout << "pending" << std::endl;
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