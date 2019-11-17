/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** ECS Entity pool definition
*/

#include "EntityPool.hpp"

ECS::EntityPool::EntityPool():
	_counter(0)
{}

ECS::EntityID	ECS::EntityPool::takeID()
{
	if (_unused.empty())
		return _counter++;
	else {
		auto id = _unused.front();
		_unused.pop();
		return id;
	}
}

void		ECS::EntityPool::returnID(EntityID id)
{
	_unused.push(id);
}

size_t		ECS::EntityPool::getPopSize() const
{
	return _counter - _unused.size();
}

size_t		ECS::EntityPool::getUnusedSize() const
{
	return _unused.size();
}