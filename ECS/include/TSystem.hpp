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
#include "TEvent.hpp"
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
				_componentsTables(std::forward<TComponentTable<Components> &>(tables)...),
				_scheduler(&scheduler)
			{}

			virtual ~TSystem() = default;

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
			void	declareTask(const typename Task::ExecutorType &task)
			{
				try {
					auto	taskRemover = [this](TaskNode *task){_scheduler->removeTask(*task);};
					_tasks.emplace_back(
						&_scheduler->postTask(
							TTask<TaskComponents...>(
								std::get<TableNonConst<TaskComponents> &>(_componentsTables)...,
								task
							)
						),
					taskRemover);
				} catch(const std::exception& e) {
					std::cerr << __func__ << " : " << e.what() << '\n';
				}
			}

			template<typename EventData, typename... HandlerComponents>
			void	on(std::function<void(const EventData &event, EntityID source, MaybeConstTable<HandlerComponents> &...)> handler)
			{
				declareTask<const TEvent<EventData>, HandlerComponents...>([=](const TComponentTable<TEvent<EventData>> &events, MaybeConstTable<HandlerComponents> &... tables){
					for (auto &eventQueue : events) {
						for (auto &event : *eventQueue) {
							handler(event, eventQueue.getID(), std::forward<MaybeConstTable<HandlerComponents> &>(tables)...);
						}
					}
				});
			}

			///
			///@brief Free for override event triggered on call to reload
			///
			///
			virtual void	onLoad() {}

			decltype(auto)	getScheduler()
			{
				return *_scheduler;
			}

			decltype(auto)	getScheduler() const
			{
				return *_scheduler;
			}

			using TaskSubscription = std::unique_ptr<TaskNode, std::function<void(TaskNode *)>>;

		private:

			TablePacket						_componentsTables;
			Scheduler						*_scheduler;
			std::vector<TaskSubscription>	_tasks;
	};
}

#endif /* !TSYSTEM_HPP_ */
