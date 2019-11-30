/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Game instance object definition
*/

#include "Instance.hpp"

Instance::ID	Instance::nextID = 0;

Instance::Instance():
	systems{*scheduler, *components},
	_id{nextID++}
{}

Instance::ID	Instance::getID() const
{
	return _id;
}
