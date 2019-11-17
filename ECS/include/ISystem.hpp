/*
** EPITECH PROJECT, 2019
** rtpye
** File description:
** ECS system interface
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

namespace ECS {

	///
	///@brief System interface
	///
	/// Used mostly for runtime binding of containers
	///
	class ISystem {
		public:

			virtual ~ISystem();

			///
			///@brief reload the system
			///
			///
			virtual void	reload();

		protected:
		private:
	};
}

#endif /* !ISYSTEM_HPP_ */
