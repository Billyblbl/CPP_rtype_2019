/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** JSONValue
*/

#include "JSONValue.hpp"
#include "JSONParser.hpp"

// JSONValue::JSONValue()
// {
// }

// JSONValue::~JSONValue()
// {
// }

JSONValue			&JSONValue::operator[](size_t idx)
{
	return std::get<Array>(_val)[idx];
}

const JSONValue	&JSONValue::operator[](size_t idx) const
{
	return std::get<Array>(_val)[idx];
}

JSONValue			&JSONValue::operator[](const std::string &key)
{
	auto	&map = std::get<Object>(_val);
	auto	it = map->find(key);
	if (it == map->end()) {
		return *map->emplace(key, std::make_unique<JSONValue>(Null{})).first->second;
	}
	return *it->second;
}

const JSONValue		&JSONValue::operator[](const std::string &key) const
{
	return *std::get<Object>(_val)->at(key);
}

bool				JSONValue::isNull() const
{
	return std::get_if<Null>(&_val) == nullptr;
}

JSONValue::Value		&JSONValue::getVal()
{
	return _val;
}

const JSONValue::Value	&JSONValue::getVal() const
{
	return _val;
}

JSONValue				JSONValue::parseJSON(const std::string &input)
{
	return JSONParser{}.parse(input);
}

JSONValue				JSONValue::loadJSON(const std::string &path)
{
	return JSONParser{}.load(path);
}