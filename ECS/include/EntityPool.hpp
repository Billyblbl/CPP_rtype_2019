/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** ECS entity pool
*/

#ifndef ENTITYPOOL_HPP_
#define ENTITYPOOL_HPP_

#include <cinttypes>
#include <queue>
#include <cstddef>

namespace ECS {

	///
	///@brief ID type used to reference an entity
	///
	///
	using EntityID = uint64_t;

	class EntityPool {
		public:
			EntityPool();

			EntityID	takeID();
			void		returnID(EntityID id);

			size_t		getPopSize() const;
			size_t		getUnusedSize() const;

		protected:
		private:

			EntityID				_counter;
			std::queue<EntityID>	_unused;
	};
}

#endif /* !ENTITYPOOL_HPP_ */
