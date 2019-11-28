/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** event mediator object definition
*/

#include <optional>
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
	while (!_pending->empty()) {
		auto maybeEvent = [&]()->std::optional<EventHolder> {
			auto	locked = *_pending;
			if (!locked->empty()) {
				auto	event = std::move(locked->front());
				locked->pop();
				return std::optional{event};
			} else
				return std::nullopt;
		}();
		if (maybeEvent.has_value()) {
			auto	[type, event] = maybeEvent.value();
			for (auto &listener : _listeners[type])
				listener->notify(event);
		}
	}
}
