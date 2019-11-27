/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** rtype client
*/
#include "Renderer.hpp"
#include "Instance.hpp"
#include "AssetCache.hpp"

struct CachedTexture {
	CachedTexture(const std::string &path)
	{
		texture.loadFromFile(path);
	}

	sf::Texture	texture;
};

int	main()
{
	auto Texture = AssetCache::getGlobalCache().load<CachedTexture>("../assets/sprites/r-typesheet1.gif");
	Instance	instance;
	instance.components->addTable<Renderer::UniqueWindow>();
	instance.components->addTable<sf::Sprite>();
	instance.systems->addSystem<Renderer>(
		instance.components->getTable<Renderer::UniqueWindow>(),
		instance.components->getTable<sf::Sprite>()
	);
	auto WindowEntity = instance.entities->takeID();
	auto SpriteTest = instance.entities->takeID();
	instance.components->getTable<Renderer::UniqueWindow>().emplace(WindowEntity, std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), std::string("R-Engine")));
	instance.components->getTable<sf::Sprite>().emplace(SpriteTest, Texture->texture);
	while(true) {
		if (instance.scheduler->hasAvailableTask()) {
			auto task = instance.scheduler->takeTask();
			(*task)();
			instance.scheduler->reportTask(task);
		}
	}
	return 0;
}