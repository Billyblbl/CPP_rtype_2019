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

///
///@brief mutex guarded type
///
/// all operation made through this wrapper template will be
/// executed each under their own lock guard
///
///@tparam T Object wrapped
///@tparam std::mutex mutex type used to guard the object, defaulted to std::mutex
///
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

		///
		///@brief Arrays subscript operator
		///
		/// call the object's array subscript operator under guard
		///
		///@tparam I Index type forwarded to the object's array subscript operator
		///@tparam Guard Guard type used to lock the mutex, defaulted to std::lock_guard<Mutex>
		///@param i Indexforwarded to the object's array subscript operator
		///
		template<typename I, typename Guard = std::lock_guard<Mutex>>
		decltype(auto) operator[](I &&i)
		{
			Guard	g(_mutex);
			return _obj[std::forward<I>(i)];
		}

		///
		///@brief Arrays subscript const operator
		///
		/// call the object's array subscript const operator under guard
		///
		///@tparam I Index type forwarded to the object's array subscript const operator
		///@tparam Guard Guard type used to lock the mutex, defaulted to std::lock_guard<Mutex>
		///@param i Index forwarded to the object's array subscript const operator
		///
		template<typename I, typename Guard = std::lock_guard<Mutex>>
		decltype(auto) operator[](I &&i) const
		{
			Guard	g(_mutex);
			return _obj[std::forward<I>(i)];
		}

		///
		///@brief Call operator
		///
		/// call the object's call operator under guard
		///
		///@tparam Args Types of the arguments forwarded to the object's call operator
		///@tparam Guard Guard type used to lock the mutex, defaulted to std::lock_guard<Mutex>
		///@param args Arguments forwarded to the object's call operator
		///
		template<typename... Args, typename Guard = std::lock_guard<Mutex>>
		decltype(auto) operator()(Args&&... args)
		{
			Guard	g(_mutex);
			return _obj(std::forward<Args>(args)...);
		}

		///
		///@brief Call operator
		///
		/// call the object's call const operator under guard
		///
		///@tparam Args Types of the arguments forwarded to the object's call const operator
		///@tparam Guard Guard type used to lock the mutex, defaulted to std::lock_guard<Mutex>
		///@param args Arguments forwarded to the object's call const operator
		///
		template<typename... Args, typename Guard = std::lock_guard<Mutex>>
		decltype(auto) operator()(Args&&... args) const
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
