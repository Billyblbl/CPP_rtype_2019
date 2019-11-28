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
		auto &windowTable = instance.components->getTable<Renderer::UniqueWindow>();
		auto &spriteTable = instance.components->getTable<sf::Sprite>();
		instance.systems->addSystem<Renderer>(windowTable, spriteTable);
		auto WindowEntity = instance.entities->takeID();
		auto SpriteTest = instance.entities->takeID();
		instance.components->getTable<Renderer::UniqueWindow>().emplace(WindowEntity, std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), std::string("R-Engine")));
		instance.components->getTable<sf::Sprite>().emplace(SpriteTest, Texture->texture);
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