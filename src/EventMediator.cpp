/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** event mediator object definition
*/

#include "EventMediator.hpp"

EventMediator::EventMediator(Scheduler &scheduler)
{
	scheduler.postTask(ECS::TTask<>([this](){
		processPendingEvents();
	}));
}

// EventMediator::~EventMediator()
// {
// }

void	EventMediator::processPendingEvents()
{
	while (!_pending.empty()) {
		auto	[type, event] = std::move(_pending.front());
		_pending.pop();
		for (auto &listener : _listeners[type])
			listener->notify(event);
	}
}
