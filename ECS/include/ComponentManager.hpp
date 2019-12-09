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
#include <algorithm>
#include "IComponentTable.hpp"
#include "TComponentTable.hpp"

namespace ECS {

	///
	///@brief Contains all tables of components of a single instance
	///
	///
	class ComponentManager {
		public:

			using TableEntry = std::pair<std::type_index, std::unique_ptr<IComponentTable>>;
			struct Comparator
			{
				bool operator() ( const TableEntry &table, std::type_index type ) const { return table.first < type; }
				bool operator() ( std::type_index type, const TableEntry &table ) const { return table.first > type; }
			};

			template<typename ComponentType>
			decltype(auto)	find()
			{
				auto	its = std::lower_bound(begin(), end(), typeid(ComponentType), Comparator{});
				if (its == end() || its->first != typeid(ComponentType))
					return end();
				else
					return its;
			}


			///
			///@brief Get a Table of components
			///
			///@tparam ComponentType of the table to retreive
			///
			template<typename ComponentType>
			decltype(auto)	getTable()
			{
				// std::cout << "tables.size == " << _tables.size() << std::endl;
				// for (auto &entry : _tables) {
				// 	std::cout << entry.first.name() << ' ' << entry.first.hash_code() << std::endl;
				// }
				// std::cout << __func__ << " : " << "type : " << typeid(ComponentType).name() << std::endl;
				static_assert(std::is_base_of_v<IComponentTable, TComponentTable<ComponentType>>, "not a component table");
				auto it = find<ComponentType>();
				if (it == end())
					throw std::runtime_error(std::string(__func__) + " : Table not found : " + typeid(ComponentType).name());
				auto	*table = it->second.get();
				return *static_cast<TComponentTable<ComponentType> *>(table);
			}

			///
			///@brief Get a Table of components
			///
			///@tparam ComponentType of the table to retreive
			///
			template<typename ComponentType>
			decltype(auto)	getTable() const
			{
				// for (auto &entry : _tables) {
				// 	std::cout << entry.first.name() << ' ' << entry.first.hash_code() << std::endl;
				// }
				// std::cout << __func__ << " : " << "type : " << typeid(ComponentType).name() << std::endl;
				static_assert(std::is_base_of_v<IComponentTable, TComponentTable<ComponentType>>, "not a component table");
				auto it = find<ComponentType>();
				if (it == end())
					throw std::runtime_error(std::string(__func__) + " : Table not found : " + typeid(ComponentType).name());
				auto	*table = it->second.get();
				return *static_cast<TComponentTable<ComponentType> *>(table);
			}

			///
			///@brief Adds a table of components
			///
			///@tparam ComponentType types of the components contained in the new table
			///
			template<typename ComponentType>
			void		addTable()
			{
				// std::cout << __func__ << " : " << "type : " << typeid(ComponentType).name() << std::endl;
				static_assert(std::is_base_of_v<IComponentTable, TComponentTable<ComponentType>>, "not a component table");

				auto	it = find<ComponentType>();
				if (it != end())
					throw std::runtime_error(std::string(__func__) + " : Table already found : " + typeid(ComponentType).name());
				// std::cout << __func__ << " tables.size = " << _tables.size() << std::endl;
				_tables.emplace(
					std::upper_bound(begin(), end(), typeid(ComponentType), Comparator{}),
					std::type_index(typeid(ComponentType)),
					std::make_unique<TComponentTable<ComponentType>>()
				);
				// std::cout << __func__ << " tables.size = " << _tables.size() << std::endl;
				// std::sort(begin(), end(), [](auto &a, auto &b){
				// 	return a.first < b.first;
				// });
			}

			///
			///@brief removes a table of components
			///
			///@tparam ComponentType types of the components contained in the table to remove
			///
			template<typename ComponentType>
			void		removeTable()
			{
				static_assert(std::is_base_of_v<IComponentTable, TComponentTable<ComponentType>>, "not a component table");
				auto	it = find<ComponentType>();
				if (it == end())
					throw std::runtime_error(std::string(__func__) + " : Table not found : " + typeid(ComponentType).name());
				_tables.erase(it);
			}

			template<typename ComponentType>
			bool		hasTable()
			{
				static_assert(std::is_base_of_v<IComponentTable, TComponentTable<ComponentType>>, "not a component table");
				return find<ComponentType>() != end();
			}

			decltype(auto)	begin()
			{
				return _tables.begin();
			}

			decltype(auto)	begin() const
			{
				return _tables.begin();
			}

			decltype(auto)	end()
			{
				return _tables.end();
			}

			decltype(auto)	end() const
			{
				return _tables.end();
			}

		protected:
		private:

			// using TableMap = std::unordered_map<std::type_index, std::unique_ptr<IComponentTable>>;
			using TableMap = std::vector<TableEntry>;

			TableMap	_tables;

	};
}

#endif /* !COMPONENTMANAGER_HPP_ */
