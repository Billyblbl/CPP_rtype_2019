/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Event listener template
*/

#ifndef TLISTENER_HPP_
#define TLISTENER_HPP_

#include "IListener.hpp"

///
///@brief Event Listener template
///
///@tparam EventType Event type listened to by the listener
///
template<typename EventType>
class TListener : public IListener {
	public:

		///
		///@brief Destroy the TListener object
		///
		///
		virtual ~TListener() = default;

		///
		///@brief Notify the listener of an event
		///
		///
		void	notify(const std::any &event)
		{
			onNotify(std::any_cast<EventType>(event));
		}

		///
		///@brief Event reaction to the event type
		///
		///
		void	onNotify(const EventType &) = 0;

	protected:
	private:
};

#endif /* !TLISTENER_HPP_ */
