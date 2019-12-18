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
#include "InstanceCalls.hpp"
#include "TComponentTable.hpp"
#include "TSystem.hpp"
#include "Component.hpp"
#include "TAsset.hpp"
#include "JSONValue.hpp"

struct TextureChangedImpl {};

struct CachedTextureImpl {
	sf::Texture	texture;
	inline CachedTextureImpl(const std::string &path)
	{
		texture.loadFromFile(path);
	}
};

struct ParsedWindowImpl {
	inline ParsedWindowImpl(const JSONValue &params):
		handle(std::make_unique<sf::RenderWindow>(sf::VideoMode(
			params["width"].get<JSONValue::Numberi>(),
			params["height"].get<JSONValue::Numberi>()
		), params["title"].get<JSONValue::String>()))
	{}

	std::unique_ptr<sf::RenderWindow>	handle;
};

class Renderer : public ECS::TSystem<
	ParsedWindowImpl,
	sf::Sprite,
	Scale,
	Position,
	Rotation,
	ECS::TAsset<CachedTextureImpl>,
	TEvent<TextureChangedImpl>,
	TEvent<sf::Event>,
	TEvent<InstanceCalls::Type>
> {
	public:

		using UniqueWindow = ParsedWindowImpl;

		using TextureChanged = TextureChangedImpl;

		using CachedTexture = CachedTextureImpl;

		template<typename... Components>
		Renderer(Scheduler &scheduler, ECS::TComponentTable<Components> &... tables):
			ECS::TSystem<Components...>(scheduler, tables...)
		{}

	private :
		void    onLoad() override;
};

#endif /* !RENDERER_HPP_ */
