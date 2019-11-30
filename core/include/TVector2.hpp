/*
** EPITECH PROJECT, 2019
** r-type
** File description:
** vector2 template
*/

#ifndef TVECTOR2_HPP_
#define TVECTOR2_HPP_

#include <stdexcept>

template<typename num>
struct TVector2 {

	num x;
	num y;

	TVector2(num _x, num _y) :
		x(_x),
		y(_y)
	{}
	TVector2(const TVector2 &)  = default;
	TVector2(TVector2 &&)       = default;

	TVector2	&operator=(const TVector2 &) = default;
	TVector2	&operator=(TVector2 &&) = default;

	TVector2    operator+(const TVector2 &rhs) {
		return {this->x + rhs.x, this->y + rhs.y};
	}

	TVector2    &operator+=(const TVector2 &rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		return  *this;
	}

	TVector2    operator-(const TVector2 &rhs) {
		return  {this->x - rhs.x, this->y - rhs.y};
	}

	TVector2    &operator-=(const TVector2 &rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;
		return  *this;
	}

	TVector2    operator*(const num &rhs) {
		return  {this->x * rhs, this->y * rhs};
	}

	TVector2    &operator*=(const num &rhs) {
		this->x *= rhs;
		this->y *= rhs;
		return  *this;
	}

	TVector2    operator/(const num &rhs) {
		if (rhs == 0)
			throw std::runtime_error("Division by zero");
		return  {this->x / rhs ,this->y / rhs};
	}

	TVector2    &operator/=(const num &rhs) {
		if (rhs == 0)
			throw std::runtime_error("Division by zero");
		this->x /= rhs;
		this->y /= rhs;
		return  *this;
	}

	TVector2    operator%(const num &rhs) {
		if (rhs == 0)
			throw std::runtime_error("Modulo by zero");
		return  {this->x % rhs ,this->y % rhs};
	}

	TVector2    &operator%=(const num &rhs) {
		if (rhs == 0)
			throw std::runtime_error("Modulo by zero");
		this->x %= rhs;
		this->y %= rhs;
		return  *this;
	}
};

#endif /* !TVECTOR2_HPP_ */
