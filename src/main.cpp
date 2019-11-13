/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** main
*/

#include <Entity.hpp>

int	main(int, char *[])
{
	Entity	ent;
	ent.addComponent<int>(50);
	std::lock_guard	lock (ent);
	return *ent.getComponent<int>();
}
