/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** thread safe locked reference template
*/

#ifndef TLOCKEDREF_HPP_
#define TLOCKEDREF_HPP_

#include <mutex>

///
///@brief Locking reference template
///
/// RAII style tool to force access of object through locking guard
///
///@tparam T 
///
template<typename T, class MutexLike>
class TLockedRef {
	public:

		///
		///@brief Guard type used by the locked reference
		///
		///
		using Guard = std::lock_guard<MutexLike>;

		///
		///@brief Mutex type locked by the locked reference
		///
		///
		using Mutex = MutexLike;

		///
		///@brief Construct a new TLockedRef object
		///
		///@param ref 
		///@param mutex 
		///
		TLockedRef(T &ref, Mutex &mutex):
			_ref(ref),
			_guard(mutex)
		{}

		///
		///@brief object dereferencer operator
		///
		///
		T	&operator*()
		{
			return _ref;
		}

		///
		///@brief member dereferencer operator
		///
		///
		T	*operator->()
		{
			return &_ref;
		}

		///
		///@brief object dereferencer const operator
		///
		///
		const T	&operator*() const
		{
			return _ref;
		}

		///
		///@brief member dereferencer const operator
		///
		///
		const T	*operator->() const
		{
			return &_ref;
		}

		operator T&()
		{
			return _ref;
		}

		operator const T&() const
		{
			return _ref;
		}

	protected:
	private:

		T		&_ref;
		Guard	_guard;
};

#endif /* !TLOCKEDREF_HPP_ */
