/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Manifest
*/

#include "Controller.hpp"
#include "Kinematic.hpp"
#include "Manifest.hpp"

EXPOSABLE_COMPONENTS {
	makeComponentEntry<Controller>("actors.controller"),
	makeEventEntry<Controller::BeamFire>("actors.fireBeamEvent")
};

EXPOSE_COMPONENTS

EXPOSABLE_SYSTEMS {
	makeSystemEntry<Kinematic>("actors.kinematic")
};

EXPOSE_SYSTEMS
