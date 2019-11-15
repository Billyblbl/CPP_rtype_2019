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

template<typename... Components>
class TTask {
	public:

		template<typename Component>
		using TableNonConst = TComponentTable<std::remove_const_t<Component>>;

		///
		///@brief component tables where const qualifier is moved from the
		/// components type to the table type
		///
		///
		template<typename Component>
		using MaybeConstTable = std::conditional_t<
			/* if */std::is_const_v<Component>,
			/* then */const TableNonConst<Component>,
			/* else */TableNonConst<Component>
		>;

		using TablePacket = std::tuple<MaybeConstTable<Components> &...>;
		using ExecutorType = std::function<void (MaybeConstTable<Components> &...)>;

		TTask(MaybeConstTable<Components> &... tables, ExecutorType executor):
			_componentsTables(std::forward<MaybeConstTable<Components> &>(tables)...),
			_executor(executor)
		{}

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
