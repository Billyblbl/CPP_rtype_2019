/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Event listener interface | acting as pseudo-"any" limited to specializations of listener template
*/

#ifndef ILISTENER_HPP_
#define ILISTENER_HPP_

#include <any>

class IListener {
	public:
		virtual ~IListener() = default;

		virtual void	notify(const std::any &event) = 0;

	protected:
	private:
};

#endif /* !ILISTENER_HPP_ */
