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

namespace ECS {

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
			[[deprecated]] operator auto &()
			{
				return _components;
			}

			///
			///@brief Const conversion operator into internal collection type
			///
			///
			[[deprecated]] operator const auto &()
			{
				return _components;
			}

			///
			///@brief Get the internal collection object
			///
			///
			[[deprecated]] auto	&get()
			{
				return _components;
			}

			///
			///@brief Get the const internal collection object
			///
			///
			[[deprecated]]const auto	&get() const
			{
				return _components;
			}

			///
			///@brief Member dereferencer of the internal collection object
			///
			///
			[[deprecated]] auto		*operator->()
			{
				return &_components;
			}

			///
			///@brief Member const dereferencer of the internal const collection object
			///
			///
			[[deprecated]] const auto	*operator->() const
			{
				return &_components;
			}


			//std binary_search only returns a bool for some reason so this is indexer operator
			// is a reimplementation of the algorithm that actually returns a thing
			auto	&operator[](EntityID ent)
			{
				auto it = find(ent);
				if (it != end())
					return *it;
				else
					throw std::invalid_argument(std::string(__func__) + " : Cannot find component of ID" + ent);
			}

			auto	&operator[](EntityID ent) const
			{
				auto it = find(ent);
				if (it != end())
					return *it;
				else
					throw std::invalid_argument(std::string(__func__) + " : Cannot find component of ID" + ent);
			}

			auto	find(EntityID ent)
			{
				auto	begin = begin();
				auto	end = end();
				for (auto middle = begin + end / 2; begin < end - 1; middle = begin + end / 2) {
					if (middle->getID() < ent) {
						begin = middle + 1;
					} else if (middle->getID() > ent) {
						end = middle;
					} else
						return middle;
				}
				return end();
			}

			auto	find(EntityID ent) const
			{
				auto	begin = begin();
				auto	end = end();
				for (auto middle = begin + end / 2; begin < end - 1; middle = begin + end / 2) {
					if (middle->getID() < ent) {
						begin = middle + 1;
					} else if (middle->getID() > ent) {
						end = middle;
					} else
						return middle;
				}
				return end();
			}

			auto	begin()
			{
				return _components.begin();
			}

			auto	end()
			{
				return _components.end();
			}

			auto	begin() const
			{
				return _components.begin();
			}

			auto	end() const
			{
				return _components.end();
			}

			template<typename... Args>
			auto	&emplace(EntityID id , Args&&... args)
			{
				return _components.emplace_back(id, std::forward<Args>(args)...);
			}

			using TableType = std::vector<TComponent<ComponentType>>;
			using iterator = typename TableType::iterator;

			void	erase(iterator it)
			{
				_components.erase(it);
			}

			void	erase(iterator begin, iterator end)
			{
				_components.erase(begin, end);
			}

			void	remove(EntityID id)
			{
				auto	it = find(id);
				if (it == end())
					throw std::invalid_argument(std::string(__func__) + " : Component not found : " + id);
				erase(it);
			}

		protected:
		private:
			TableType			_components;
			std::type_index		_type;
	};

	///
	///@brief Table of forcibly non-const components
	///
	/// Utility type.
	/// Makes a component table type out of a component table while removing
	/// constant qualifier from the comopnent type
	///
	///@warning meant to be used with MaybeConstTable template, other uses are dangerous
	///
	///@tparam Component
	///
	template<typename Component>
	using TableNonConst = TComponentTable<std::remove_const_t<Component>>;

	///
	///@brief component tables const qualifier manipulator
	///
	/// Makes a component table type where any const qualifier is moved from the
	/// components type to the table type
	///
	template<typename Component>
	using MaybeConstTable = std::conditional_t<
		/* if */std::is_const_v<Component>,
		/* then */const TableNonConst<Component>,
		/* else */TableNonConst<Component>
	>;
}

#endif /* !TCOMPONENTTABLE_HPP_ */
