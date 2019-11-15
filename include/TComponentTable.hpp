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

template<typename ComponentType>
class TComponentTable : public IComponentTable {
	public:

		template<typename... Args>
		TComponentTable(Args&&... args):
			_components(std::forward<Args>(args)...),
			_type(typeid(ComponentType))
		{}

		std::type_index	getTypeID() const override
		{
			return _type;
		}

		operator auto &()
		{
			return _components;
		}

		operator const auto &()
		{
			return _components;
		}

		auto	&get()
		{
			return _components;
		}

		const auto	&get() const
		{
			return _components;
		}

		auto		*operator->()
		{
			return &_components;
		}

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
