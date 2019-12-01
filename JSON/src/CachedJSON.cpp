/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** CachedJSON
*/

#include "CachedJSON.hpp"

CachedJSON::CachedJSON(const std::string &path):
	value(JSONValue::loadJSON(path))
{}
