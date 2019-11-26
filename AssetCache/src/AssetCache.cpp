/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** asset cahce definition
*/

#include "AssetCache.hpp"

AssetCache  &AssetCache::getGlobalCache()
{
	static  AssetCache  cache;
	return cache;
}