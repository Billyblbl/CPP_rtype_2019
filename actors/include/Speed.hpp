/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Speed
*/

#ifndef SPEED_HPP_
#define SPEED_HPP_

#include "JSONValue.hpp"

struct	Speed {
	float value;
	inline Speed(const JSONValue &params):
		value(params.get<JSONValue::Numberf>())
	{}
};

#endif /* !SPEED_HPP_ */
