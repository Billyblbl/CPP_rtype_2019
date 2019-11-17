/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** ECS system template
*/

#ifndef TSYSTEM_HPP_
#define TSYSTEM_HPP_

#include <tuple>
#include "ISystem.hpp"
#include "TComponentTable.hpp"
#include "TTask.hpp"

namespace ECS {

	///
	///@brief ECS System Template
	///
	///@tparam Components Component types accessed by the system
	///
	template<typename... Components>
	class TSystem : public ISystem {
		public:

			TSystem(TComponentTable<Components>&... tables):
				_componentsTables(std::forward<TComponentTable<Components>>(tables)...)
			{}

			///
			///@brief Reload the system
			///
			///
			void	reload()
			{
				onReload();
			}



			///
			///@brief interna tuple types of references to managed components' tables
			///
			///
			using TablePacket = std::tuple<TComponentTable<Components> &...>;


		protected:

			///
			///@brief Declares a task of corresponding components with the given executor
			///
			/// Provides task with accessible components tables
			///
			///@tparam TaskComponents Components used by the task
			///@param task executor used to define the actions taken by the task
			///@return auto Built task
			///
			template<typename... TaskComponents, class Task = TTask<TaskComponents...>>
			auto	declareTask(typename Task::ExecutorType &task)
			{
				return TTask<TaskComponents...>(
					std::get<TableNonConst<TaskComponents>>(_componentsTables)...,
					task
				);
			}

			///
			///@brief Free for override event triggered on call to reload
			///
			///
			virtual void	onReload() {}

		private:

			TablePacket	_componentsTables;
	};
}

#endif /* !TSYSTEM_HPP_ */
