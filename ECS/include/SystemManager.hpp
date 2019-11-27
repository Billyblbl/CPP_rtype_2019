/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** ECS ssytem manager object
*/

#ifndef SYSTEMMANAGER_HPP_
#define SYSTEMMANAGER_HPP_

#include <typeindex>
#include <unordered_map>
#include <memory>
#include "ISystem.hpp"
#include "TSystem.hpp"
#include "Scheduler.hpp"

namespace ECS {

	///
	///@brief Contains all sysytems of a single instance
	///
	///
	class SystemManager {
		public:

			SystemManager(Scheduler &sheduler):
				_scheduler(&sheduler)
			{}

			template<typename SystemType>
			auto		&getSystem()
			{
				static_assert(std::is_base_of_v<ISystem, SystemType>, "not a System");
				auto	*system = _systems.at(typeid(SystemType)).get();
				return *static_cast<SystemType *>(system);
			}

			template<typename SystemType>
			const auto	&getSystem() const
			{
				static_assert(std::is_base_of_v<ISystem, SystemType>, "not a System");
				auto	*system = _systems.at(typeid(SystemType)).get();
				return *static_cast<SystemType *>(system);
			}

			template<typename SystemType, typename... Args>
			void		addSystem(Args&&... args)
			{
				static_assert(std::is_base_of_v<ISystem, SystemType>, "not a System");
				_systems.emplace(
					std::type_index(typeid(SystemType)),
					std::unique_ptr<ISystem>(
						std::make_unique<SystemType>(*_scheduler, std::forward<Args>(args)...)
					)
				);
			}

			template<typename SystemType>
			void		removeSystem()
			{
				static_assert(std::is_base_of_v<ISystem, SystemType>, "not a System");
				_systems.erase(typeid(SystemType));
			}

			template<typename SystemType>
			bool		hasSystem()
			{
				static_assert(std::is_base_of_v<ISystem, SystemType>, "not a System");
				return _systems.find(typeid(SystemType)) != _systems.end();
			}

			void	rebind(Scheduler &scheduler)
			{
				_scheduler = &scheduler;
				for (auto &[type, system] : _systems) {
					system->rebind(scheduler);
				}
			}

			void	reload()
			{
				for (auto &[type, system] : _systems) {
					system->reload();
				}
			}

		protected:
		private:

			using SystemMap = std::unordered_map<std::type_index, std::unique_ptr<ISystem>>;

			SystemMap	_systems;
			Scheduler	*_scheduler;
	};
}

#endif /* !SYSTEMMANAGER_HPP_ */
