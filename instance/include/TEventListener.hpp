/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** New event listener model template
*/

#ifndef TEVENTLISTENER_HPP_
#define TEVENTLISTENER_HPP_

#include <type_traits>
#include "TSystem.hpp"
#include "ComponentManager.hpp"
#include "Scheduler.hpp"

template<class EventType, typename... Components>
class [[deprecated]] TEventListener : pubic ECS::TSystem<std::queue<EventType>, Components...> {
	public:

		using EventOrigin = std::queue<EventType>;

		TEventListener(Scheduler &scheduler, ECS::ComponentManager &manager):
			ECS::System{manager.getTable<EventOrigin>(), manager.getTable<Components>()...},
			_task{
				declareTask<EventOrigin, Components...>([this](const auto &events, auto&&... ){
					for (auto &event : events) {
						onNotify(event, event.getID());
					}
				})
			},
			_scheduler{scheduler}
		{}

		virtual ~TEventListener()
		{
			_scheduler.removeTask(_task);
		}

		virtual onNotify(const EventType event, ECS::EntityID id) = 0;

	protected:
	private:
		TaskNode	&_task;
		Scheduler	&_scheduler;

};

#endif /* !TEVENTLISTENER_HPP_ */
