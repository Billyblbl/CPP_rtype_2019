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

namespace ECS {

	///
	///@brief Component table interface
	///
	/// Used mostly for runtime binding of containers
	///
	class IComponentTable {
		public:

			virtual ~IComponentTable() = default;

			///
			///@brief Get the Type ID of the components in the table
			///
			///
			virtual std::type_index	getTypeID() const = 0;

		protected:
		private:
	};
}

#endif /* !ICOMPONENTTABLE_HPP_ */
