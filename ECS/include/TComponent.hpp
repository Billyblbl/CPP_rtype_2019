/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** ECS component template
*/

#ifndef TCOMPONENT_HPP_
#define TCOMPONENT_HPP_

#include "EntityPool.hpp"

namespace ECS {

	///
	///@brief ECS Component template
	///
	///@tparam ObjectT usable type of the component
	///
	template<typename ObjectT>
	class TComponent {
		public:

			///
			///@brief Usable internal type
			///
			///
			using Object = ObjectT;

			///
			///@brief Construct a new TComponent object
			///
			///@tparam Args Construction args types
			///@param args Construction args
			///
			template<typename... Args>
			TComponent(EntityID parent, Args&&... args):
				_parent(parent),
				_obj(std::forward<Args>(args)...)
			{}

			TComponent(TComponent &&) = default;

			TComponent &operator=(TComponent &&) = default;

			///
			///@brief Conversion operator into the usable internal type
			///
			///
			operator Object &()
			{
				return _obj;
			}

			///
			///@brief Const Conversion operator into the usable internal type
			///
			///
			operator const Object &() const
			{
				return _obj;
			}

			///
			///@brief Dereferencer operator
			///
			///@return Object& internal usable object
			///
			Object			&operator*()
			{
				return _obj;
			}

			///
			///@brief Const Dereferencer operator
			///
			///@return const Object& internal usable object
			///

			const Object	&operator*() const
			{
				return _obj;
			}


			///
			///@brief Member dereferencer operator
			///
			///@return Object* internal usable object ptr
			///
			Object			*operator->()
			{
				return &_obj;
			}

			///
			///@brief Member dereferencer operator
			///
			///@return const Object* internal usable object ptr
			///
			const Object	*operator->() const
			{
				return &_obj;
			}

			///
			///@brief Get the ID of the parent entity
			///
			///
			EntityID		getID() const
			{
				return _parent;
			}

		protected:
		private:

		EntityID	_parent;
		Object		_obj;
	};
}

#endif /* !TCOMPONENT_HPP_ */
