/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Manifest for sfml plugin
*/

#include "Manifest.hpp"
#include "Renderer.hpp"
#include "Inputs.hpp"
#include "Animator.hpp"
#include "Animations.hpp"

//Define all components exposable as R-Engine Plugin
EXPOSABLE_COMPONENTS {
	makeComponentEntry<Renderer::UniqueWindow, true>("sfml.window"),
	makeComponentEntry<sf::Sprite>("sfml.sprite"),
	makeAssetEntry<Renderer::CachedTexture>("sfml.texture"),
	makeEventEntry<Renderer::TextureChanged>("sfml.textureChangeEvent"),
	makeEventEntry<sf::Event>("sfml.windowEvent"),
	makeComponentEntry<Animator, true>("sfml.animator")
};

//Define all systems exposable as R-Engine Plugin
EXPOSABLE_SYSTEMS {
	makeSystemEntry<Renderer>("sfml.renderer"),
	makeSystemEntry<Inputs>("sfml.inputs"),
	makeSystemEntry<Animations>("sfml.animations")
};

//Expose all previously defined exposable component
EXPOSE_COMPONENTS;

//Expose all previously defined exposable systems
EXPOSE_SYSTEMS;
