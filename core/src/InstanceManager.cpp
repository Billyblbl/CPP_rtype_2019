/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** InstanceManager
*/

#include <chrono>
#include "InstanceManager.hpp"

//debug
#include <iostream>

void	InstanceManager::onLoad()
{
	on<InstanceCalls::Type>([this](auto &call, auto source){
		switch (call) {
		case InstanceCalls::EXIT:
			std::cout << "instance manager received EXIT request" << std::endl;
			getScheduler().stop();
			break;
		case InstanceCalls::KILL:
			//temporarily same as EXIT, need to precisely define
			//what steps can be safely skipped before defining KILL
			std::cout << "instance manager received KILL request" << std::endl;
			getScheduler().stop();
			break;
		default:
			break;
		}
	});

	declareTask<Timer>([](auto &timers){
		auto	now = Timer::Clock::now();
		for (auto &timer : timers) {
			timer->last = timer->now;
			timer->now = now;
			timer->deltaT = timer->now - timer->last;
			timer->total = timer->now - timer->epoch;
		}
	});
}
