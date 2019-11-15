/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** ECS system task template
*/

#ifndef TTASK_HPP_
#define TTASK_HPP_

#include <functional>
#include <type_traits>
#include "TComponentTable.hpp"

///
///@brief ECS Task template
///
///@tparam Components used by the task on execution
///@warning Task using non-const types cannot be safely paralelized with other tasks using the same non-const types
///
template<typename... Components>
class TTask {
	public:

		///
		///@brief Table of forcibly non-const components
		///
		/// Utility type.
		/// Makes a component table type out of a component table while removing
		/// constant qualifier from the comopnent type
		///
		///@warning meant to be used with MaybeConstTable template
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

		///
		///@brief tuple type of Component table types accessible by the task
		///
		///
		using TablePacket = std::tuple<MaybeConstTable<Components> &...>;

		///
		///@brief Task callable type
		///
		///
		using ExecutorType = std::function<void (MaybeConstTable<Components> &...)>;

		///
		///@brief Construct a new TTask object
		///
		///@param tables Component tables accessible to the task
		///@param executor callable to execute on task execution
		///
		TTask(MaybeConstTable<Components> &... tables, ExecutorType executor):
			_componentsTables(std::forward<MaybeConstTable<Components> &>(tables)...),
			_executor(executor)
		{}

		///
		///@brief Call operator
		///
		///
		void	operator()()
		{
			std::apply(_executor, _componentsTables);
		}

	protected:
	private:
		TablePacket		_componentsTables;
		ExecutorType	_executor;
};

#endif /* !TTASK_HPP_ */
