/*
** EPITECH PROJECT, 2019
** r-type
** File description:
** componetn for graphical Rendering
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include "TVector2.hpp"
#include "JSONValue.hpp"

struct Scale {
    TVector2<float> value;
    inline Scale(const JSONValue &params):
        value(params[0].get<JSONValue::Numberf>(), params[1].get<JSONValue::Numberf>())
    {}
};

struct Position {
    TVector2<float> value;
    inline Position(const JSONValue &params):
        value(params[0].get<JSONValue::Numberf>(), params[1].get<JSONValue::Numberf>())
    {}
};

struct  Rotation {
    float value;
    inline Rotation(const JSONValue &params):
        value(params.get<JSONValue::Numberf>())
    {}
};

struct  Transform2f {
    TVector2<float> position;
    TVector2<float> scale;
    float           rotation;
};

#endif /* !COMPONENT_HPP_ */
