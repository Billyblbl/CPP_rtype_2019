/*
** EPITECH PROJECT, 2019
** rtpye
** File description:
** ECS system interface
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include "Scheduler.hpp"

namespace ECS {

	///
	///@brief System interface
	///
	/// Used mostly for runtime binding of containers
	///
	class ISystem {
		public:

			virtual ~ISystem() = default;

			///
			///@brief reload the system
			///
			///
			virtual void	reload() = 0;

			virtual void	rebind(Scheduler &scheduler) = 0;

		protected:
		private:
	};
}

#endif /* !ISYSTEM_HPP_ */
