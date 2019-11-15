/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** component table common interface
*/

#ifndef ICOMPONENTTABLE_HPP_
#define ICOMPONENTTABLE_HPP_

#include <cinttypes>
#include <typeindex>

class IComponentTable {
	public:
		virtual ~IComponentTable() = default;

		virtual std::type_index	getTypeID() const = 0;

	protected:
	private:
};

#endif /* !ICOMPONENTTABLE_HPP_ */
