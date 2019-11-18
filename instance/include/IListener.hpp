/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Event listener interface
*/

#ifndef ILISTENER_HPP_
#define ILISTENER_HPP_

#include <any>

///
///@brief Event listener interface
///
///
class IListener {
	public:

		///
		///@brief Destroy the IListener object
		///
		///
		virtual ~IListener() = default;

		///
		///@brief Notify the listener of an event
		///
		///
		virtual void	notify(const std::any &event) = 0;

	protected:
	private:
};

#endif /* !ILISTENER_HPP_ */
