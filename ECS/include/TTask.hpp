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

namespace ECS {

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
			///@brief Copy constructor
			///
			///
			TTask(const TTask &) = default;

			///
			///@brief Move constructor
			///
			///
			TTask(TTask &&) = default;

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
}

#endif /* !TTASK_HPP_ */
