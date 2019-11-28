/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** cached json file strutc
*/

#ifndef CACHEDJSON_HPP_
#define CACHEDJSON_HPP_

#include "JSONValue.hpp"

class CachedJSON {
	public:

		CachedJSON(const std::string &path);

		JSONValue	value;

	protected:
	private:
};

#endif /* !CACHEDJSON_HPP_ */
