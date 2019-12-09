/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Controller
*/

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include "TVector2.hpp"

constexpr TVector2<float>	UP		= {0.f, -1.f};
constexpr TVector2<float>	DOWN	= {0.f, 1.f};
constexpr TVector2<float>	LEFT	= {-1.f, 0.f};
constexpr TVector2<float>	RIGHT	= {1.f, 0.f};

struct BeamFireImpl {
	float	charge;
};

struct Controller {
	public:

		inline Controller():
			direction(0.f, 0.f),
			charging(false),
			beamCharge(0.f)
		{}

		using BeamFire = BeamFireImpl;

		TVector2<float>	direction;
		bool			firing;
		bool			charging;
		float			beamCharge;

	protected:
	private:
};

#endif /* !CONTROLLER_HPP_ */
