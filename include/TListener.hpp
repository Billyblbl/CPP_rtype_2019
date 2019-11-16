/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Event listener template
*/

#ifndef TLISTENER_HPP_
#define TLISTENER_HPP_

#include "IListener.hpp"

template<typename EventType>
class TListener : public IListener {
	public:

		virtual ~TListener() = default;

		void	notify(const std::any &event)
		{
			onNotify(std::any_cast<EventType>(event));
		}

		void	onNotify(const EventType &) = 0;

	protected:
	private:
};

#endif /* !TLISTENER_HPP_ */
