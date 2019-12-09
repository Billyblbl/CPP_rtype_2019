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

	constexpr TVector2(num _x, num _y) :
		x(_x),
		y(_y)
	{}
	constexpr TVector2(const TVector2 &)  = default;
	constexpr TVector2(TVector2 &&)       = default;

	constexpr TVector2	&operator=(const TVector2 &) = default;
	constexpr TVector2	&operator=(TVector2 &&) = default;

	constexpr TVector2    operator+(const TVector2 &rhs) const {
		return {this->x + rhs.x, this->y + rhs.y};
	}

	constexpr TVector2    &operator+=(const TVector2 &rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		return  *this;
	}

	constexpr TVector2    operator-(const TVector2 &rhs) const {
		return  {this->x - rhs.x, this->y - rhs.y};
	}

	constexpr TVector2    &operator-=(const TVector2 &rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;
		return  *this;
	}

	constexpr TVector2    operator*(const num &rhs) const {
		return  {this->x * rhs, this->y * rhs};
	}

	constexpr TVector2    &operator*=(const num &rhs) {
		this->x *= rhs;
		this->y *= rhs;
		return  *this;
	}

	constexpr TVector2    operator/(const num &rhs) const {
		if (rhs == 0)
			throw std::runtime_error("Division by zero");
		return  {this->x / rhs ,this->y / rhs};
	}

	constexpr TVector2    &operator/=(const num &rhs) {
		if (rhs == 0)
			throw std::runtime_error("Division by zero");
		this->x /= rhs;
		this->y /= rhs;
		return  *this;
	}

	constexpr TVector2    operator%(const num &rhs) const {
		if (rhs == 0)
			throw std::runtime_error("Modulo by zero");
		return  {this->x % rhs ,this->y % rhs};
	}

	constexpr TVector2    &operator%=(const num &rhs) {
		if (rhs == 0)
			throw std::runtime_error("Modulo by zero");
		this->x %= rhs;
		this->y %= rhs;
		return  *this;
	}
};

#endif /* !TVECTOR2_HPP_ */
