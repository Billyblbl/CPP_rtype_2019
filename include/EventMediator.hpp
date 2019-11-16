/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** instance Event mediator object
*/

#ifndef EVENTMEDIATOR_HPP_
#define EVENTMEDIATOR_HPP_

#include <queue>
#include <any>
#include <memory>
#include <vector>
#include "IListener.hpp"
#include "TListener.hpp"
#include "Scheduler.hpp"

class EventMediator {
	public:

		EventMediator(Scheduler &scheduler);

		template<typename EventType>
		void	on(TListener<EventType> &listener)
		{
			_listeners[typeid(EventType)].emplace_back(&listener);
		}

		template<typename EventType>
		void	removeListener(TListener<EventType> &listener)
		{
			auto &list = _listeners[typeid(EventType)];
			list.erase(std::find(list.begin(), list.end(), &listener));
			if (list.size() == 0)
				_listeners.erase(typeid(EventType));
		}

		template<typename EventType>
		void	trigger(const EventType &event)
		{
			if (_listeners.find(typeid(EventType)) != _listeners.end())
				_pending.emplace(typeid(EventType), event);
		}

	protected:
	private:

		void	processPendingEvents();

		using EventHolder = std::pair<std::type_index, std::any>;
		using ListenerList = std::vector<IListener *>;
		using ListenerMap = std::unordered_map<std::type_index, ListenerList>;

		std::queue<EventHolder>	_pending;
		ListenerMap				_listeners;
};

#endif /* !EVENTMEDIATOR_HPP_ */
