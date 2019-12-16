/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <chrono>

struct Timer {

	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<Clock>;
	using Duration = Clock::duration;

	inline Timer():
		epoch(Clock::now()),
		last(epoch),
		now(epoch),
		deltaT(0),
		total(0)
	{}

	TimePoint	epoch;
	TimePoint	last;
	TimePoint	now;
	Duration	deltaT;
	Duration	total;

};

#endif /* !TIMER_HPP_ */
