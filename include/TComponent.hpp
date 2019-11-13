/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** component template
*/

#ifndef TCOMPONENT_HPP_
#define TCOMPONENT_HPP_

#include <mutex>
#include "IComponent.hpp"
#include "TIndexedType.hpp"
#include "TLockedRef.hpp"

///
///@brief ECS Component template
///
///@tparam ComponentT Object made from the component
///
template<typename ComponentT>
class TComponent : public TIndexedType<TComponent<ComponentT>>, public IComponent {
	public:

		///
		///@brief Internal object type
		///
		///
		using Object = ComponentT;

		///
		///@brief Emplacing constructor
		///
		///@tparam Args construction args types
		///@param args construction args
		///
		template<typename... Args>
		TComponent(Args&&... args):
			_obj(std::forward<Args>(args)...)
		{}

		///
		///@brief mutex locker
		///
		///
		void	lock()
		{
			_mutex.lock();
		}

		///
		///@brief mutex unlocker
		///
		///
		void	unlock()
		{
			_mutex.unlock();
		}

		///
		///@brief Member dereferencer
		///
		/// Dereference through a locked reference
		///
		///
		auto	operator->()
		{
			return TLockedRef(_obj, _mutex);
		}

		///
		///@brief Object dereferencer
		///
		/// Dereference through a locked reference
		///
		///
		auto	operator*()
		{
			return TLockedRef(_obj, _mutex);
		}

		///
		///@brief Member const dereferencer
		///
		/// Constness should protects against race conditions
		///
		const auto	*operator->() const
		{
			return &_obj;
		}

		///
		///@brief Object const dereferencer
		///
		/// Constness should protects against race conditions
		///
		const auto	&operator*() const
		{
			return _obj;
		}

	protected:
	private:
		std::mutex	_mutex;
		Object		_obj;
};

#endif /* !TCOMPONENT_HPP_ */
