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
#include "Scheduler.hpp"

namespace ECS {

	///
	///@brief ECS System Template
	///
	///@tparam Components Component types accessed by the system
	///
	template<typename... Components>
	class TSystem : public ISystem {
		public:

			TSystem(Scheduler &scheduler, TComponentTable<Components>&... tables):
				_componentsTables(std::forward<TComponentTable<Components>>(tables)...),
				_scheduler(&scheduler)
			{}

			///
			///@brief Reload the system
			///
			///
			void	reload() override
			{
				_tasks.clear();
				onLoad();
			}



			///
			///@brief interna tuple types of references to managed components' tables
			///
			///
			using TablePacket = std::tuple<TComponentTable<Components> &...>;

			void	rebind(Scheduler &scheduler) override
			{
				_tasks.clear();
				_scheduler = &scheduler;
				onLoad();
			}

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
				auto	taskRemover = [this](TaskNode *task){_scheduler->removeTask(*task);};
				return _tasks.emplace(
					&_scheduler->postTask(TTask<TaskComponents...>(
						std::get<TableNonConst<TaskComponents>>(_componentsTables)...,
						task
					)
				), taskRemover);
			}

			///
			///@brief Free for override event triggered on call to reload
			///
			///
			virtual void	onLoad() {}

			using TaskSubscription = std::unique_ptr<TaskNode, void(TaskNode *)>;

		private:

			TablePacket						_componentsTables;
			Scheduler						*_scheduler;
			std::vector<TaskSubscription>	_tasks;
	};
}

#endif /* !TSYSTEM_HPP_ */
