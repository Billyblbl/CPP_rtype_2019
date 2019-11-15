/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** component table template
*/

#ifndef TCOMPONENTTABLE_HPP_
#define TCOMPONENTTABLE_HPP_

#include <vector>
#include <typeinfo>
#include "IComponentTable.hpp"
#include "TComponent.hpp"

///
///@brief ECS Component Table template
///
///@tparam ComponentType Usable type of the components in the table
///
template<typename ComponentType>
class TComponentTable : public IComponentTable {
	public:

		///
		///@brief Construct a new TComponentTable object
		///
		///@tparam Args Construction args types
		///@param args Construction args
		///
		template<typename... Args>
		TComponentTable(Args&&... args):
			_components(std::forward<Args>(args)...),
			_type(typeid(ComponentType))
		{}

		///
		///@brief Get the Type ID of the components in the table
		///
		///
		std::type_index	getTypeID() const override
		{
			return _type;
		}

		///
		///@brief Conversion operator into internal collection type
		///
		///
		operator auto &()
		{
			return _components;
		}

		///
		///@brief Const conversion operator into internal collection type
		///
		///
		operator const auto &()
		{
			return _components;
		}

		///
		///@brief Get the internal collection object
		///
		///
		auto	&get()
		{
			return _components;
		}

		///
		///@brief Get the const internal collection object
		///
		///
		const auto	&get() const
		{
			return _components;
		}

		///
		///@brief Member dereferencer of the internal collection object
		///
		///
		auto		*operator->()
		{
			return &_components;
		}

		///
		///@brief Member const dereferencer of the internal const collection object
		///
		///
		const auto	*operator->() const
		{
			return &_components;
		}

	protected:
	private:
		std::vector<TComponent<ComponentType>>	_components;
		std::type_index							_type;
};

#endif /* !TCOMPONENTTABLE_HPP_ */
