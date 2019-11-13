/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Entity
*/

#include "Entity.hpp"

void	Entity::lock()
{
	_mutex.lock();
}

void	Entity::unlock()
{
	_mutex.unlock();
}

