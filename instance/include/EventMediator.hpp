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
#include "TGuarded.hpp"

///
///@brief Central event mediator object
///
///
class EventMediator {
	public:

		///
		///@brief Construct a new Event Mediator object
		///
		///@param scheduler schhuler to bind to this mediator's event processing task
		///
		EventMediator(Scheduler &scheduler);

		///
		///@brief Add a listener on an event
		///
		///@tparam EventType to add the listener on
		///@param listener listener to add on the event type
		///
		template<typename EventType>
		void	on(TListener<EventType> &listener)
		{
			_listeners[typeid(EventType)].emplace_back(&listener);
		}

		///
		///@brief Removes a listener form an event
		///
		///@tparam EventType to remove a listener from
		///@param listener listener to remove
		///
		template<typename EventType>
		void	removeListener(TListener<EventType> &listener)
		{
			auto &list = _listeners[typeid(EventType)];
			list.erase(std::find(list.begin(), list.end(), &listener));
			if (list.size() == 0)
				_listeners.erase(typeid(EventType));
		}

		///
		///@brief Trigger an event
		///
		///
		template<typename EventType>
		void	trigger(const EventType &event)
		{
			if (_listeners.find(typeid(EventType)) != _listeners.end())
				_pending->emplace(typeid(EventType), event);
		}

	protected:
	private:


		///
		///@brief process task
		///
		///
		void	processPendingEvents();

		using EventHolder = std::pair<std::type_index, std::any>;
		using EventQueue = TGuarded<std::queue<EventHolder>>;
		using ListenerList = std::vector<IListener *>;
		using ListenerMap = std::unordered_map<std::type_index, ListenerList>;

		EventQueue	_pending;
		ListenerMap	_listeners;
};

#endif /* !EVENTMEDIATOR_HPP_ */
