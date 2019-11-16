/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** ECS Entity pool definition
*/

#include "EntityPool.hpp"

EntityPool::EntityPool():
	_counter(0)
{}

EntityID	EntityPool::takeID()
{
	if (_unused.empty())
		return _counter++;
	else {
		auto id = _unused.front();
		_unused.pop();
		return id;
	}
}

void		EntityPool::returnID(EntityID id)
{
	_unused.push(id);
}

size_t		EntityPool::getPopSize() const
{
	return _counter - _unused.size();
}

size_t		EntityPool::getUnusedSize() const
{
	return _unused.size();
}