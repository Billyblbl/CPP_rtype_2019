/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** component manager mapper
*/

#ifndef COMPONENTMANAGER_HPP_
#define COMPONENTMANAGER_HPP_

#include <unordered_map>
#include <memory>
#include <typeindex>
#include "IComponentTable.hpp"
#include "TComponentTable.hpp"

class ComponentManager {
	public:

		template<typename ComponentType>
		auto		&getTable()
		{
			auto	*table = _tables.at(typeid(ComponentType)).get();
			return *static_cast<TComponentTable<ComponentType> *>(table);
		}

		template<typename ComponentType>
		const auto	&getTable() const
		{
			auto	*table = _tables.at(typeid(ComponentType)).get();
			return *static_cast<TComponentTable<ComponentType> *>(table);
		}

		template<typename ComponentType>
		void		addTable()
		{
			_tables.emplace(
				std::type_index(typeid(ComponentType)),
				std::unique_ptr<IComponentTable>(std::make_unique<TComponentTable<ComponentType>>())
			);
		}

		template<typename ComponentType>
		void		removeTable()
		{
			_tables.erase(typeid(ComponentType));
		}

	protected:
	private:
		using TableMap = std::unordered_map<std::type_index, std::unique_ptr<IComponentTable>>;

		TableMap	_tables;

};

#endif /* !COMPONENTMANAGER_HPP_ */
