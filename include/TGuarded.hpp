/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** tool template
*/

#ifndef TGUARDED_HPP_
#define TGUARDED_HPP_

#include <mutex>
#include "TLockedRef.hpp"

template<typename T, typename Mutex = std::mutex>
class TGuarded {
	public:

		///
		///@brief Construct a new Guarded object
		///
		///@tparam Args Construction arguments types
		///@param args Construction arguments
		///
		template<typename... Args>
		TGuarded(Args&&... args):
			_obj(std::forward<Args>(args)...)
		{}

		///
		///@brief mutex locker
		///
		///
		auto 	lock()
		{
			_mutex.lock();
			return *this;
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
		auto	operator->()
		{
			return TLockedRef(_obj, _mutex);
		}

		///
		///@brief Object dereferencer
		///
		/// Dereference through a locked reference
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

		template<typename I, typename Guard = std::lock_guard<Mutex>>
		auto operator[](I &&i)
		{
			Guard	g(_mutex);
			return _obj[std::forward<I>(i)];
		}

		template<typename I, typename Guard = std::lock_guard<Mutex>>
		auto operator[](I &&i) const
		{
			Guard	g(_mutex);
			return _obj[std::forward<I>(i)];
		}

		template<typename... Args, typename Guard = std::lock_guard<Mutex>>
		auto operator()(Args&&... args)
		{
			Guard	g(_mutex);
			return _obj(std::forward<Args>(args)...);
		}

		template<typename... Args, typename Guard = std::lock_guard<Mutex>>
		auto operator()(Args&&... args) const
		{
			Guard	g(_mutex);
			return _obj(std::forward<Args>(args)...);
		}

	protected:
	private:

		Mutex	_mutex;
		T		_obj;
};

#endif /* !TGUARDED_HPP_ */
