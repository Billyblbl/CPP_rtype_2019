/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Manifest for core module components
*/

#include "Manifest.hpp"
#include "Component.hpp"

//Define all components exposable as R-Engine Plugin
EXPOSABLE_COMPONENTS {
	makeComponentEntry<Scale, true>("core.scale2f"),
	makeComponentEntry<Position, true>("core.position2f"),
	makeComponentEntry<Rotation, true>("core.rotation2f")
};

//Expose all previously defined exposable component
EXPOSE_COMPONENTS
