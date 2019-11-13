/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** type index globa definition
*/

#include "TypeIndexer.hpp"

TypeIndex	TypeIndexer::nextIndex = 0;

TypeIndex	TypeIndexer::attributeIndex()
{
	return nextIndex++;
}

