/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** rtype client
*/
// #include "Renderer.hpp"
#include "Instance.hpp"
#include "AssetCache.hpp"

#include <iostream>

int	main(int, char *av[])
{
	try
	{
		// auto Texture = AssetCache::getGlobalCache().load<Renderer::CachedTexture>(av[1]);
		Instance	instance(av[1]);
		// instance.components->addTable<Renderer::UniqueWindow>();
		// instance.components->addTable<sf::Sprite>();
		// instance.components->addTable<Scale>();
		// instance.components->addTable<Position>();
		// instance.components->addTable<Rotation>();
		// instance.components->addTable<ECS::TAsset<Renderer::CachedTexture>>();
		// instance.components->addTable<TEvent<Renderer::TextureChanged>>();
		// instance.components->getTable<Rotation>();
		// std::cout <<  << std::endl;
		// instance.systems->addSystem<Renderer>();
		// auto WindowEntity = instance.entities->takeID();
		// auto SpriteTest = instance.entities->takeID();
		// instance.components->getTable<Renderer::UniqueWindow>().emplace(WindowEntity, std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), std::string("R-Engine")));
		// instance.components->getTable<sf::Sprite>().emplace(SpriteTest, Texture->texture);
		// instance.components->getTable<Scale>().emplace(SpriteTest, Scale{TVector2(2.f, 2.f)});
		// instance.components->getTable<Position>().emplace(SpriteTest, Position{TVector2(100.f, 100.f)});
		// instance.components->getTable<Rotation>().emplace(SpriteTest, Rotation{2.f});
		// instance.components->getTable<ECS::TAsset<Renderer::CachedTexture>>().emplace(SpriteTest, av[1]);
		// instance.components->getTable<TEvent<Renderer::TextureChanged>>().emplace(SpriteTest);

		// for (auto &queue : instance.components->getTable<TEvent<Renderer::TextureChanged>>()) {
		// 	queue->enqueue(Renderer::TextureChanged{});
		// }
		// for (auto &window : instance.components->getTable<Renderer::UniqueWindow>()) {
		// 	auto &win = *window;
		// 	win.handle->setFramerateLimit(140);
		// }
		// instance.systems->reload();
		while(true) {
			if (instance.scheduler->hasAvailableTask()) {
				auto &&task = instance.scheduler->takeTask();
				try {
					(*task)();
				} catch(const std::exception& e) {
					std::cerr << e.what() << '\n';
				}
				instance.scheduler->reportTask(task);
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