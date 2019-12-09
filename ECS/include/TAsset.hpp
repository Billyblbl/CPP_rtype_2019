/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** TAsset
*/

#ifndef TASSET_HPP_
#define TASSET_HPP_

#include "AssetCache.hpp"

namespace ECS {

	template<typename T>
	class TAsset {
		public:
			TAsset(const std::string &path):
				_object(AssetCache::getGlobalCache().load<T>(path))
			{}

			operator T&()
			{
				return *_object;
			}

			operator const T&() const
			{
				return *_object;
			}

			T	&operator*()
			{
				return *_object;
			}

			///
			///@brief member dereferencer operator
			///
			///
			T	*operator->()
			{
				return _object.get();
			}

			///
			///@brief object dereferencer const operator
			///
			///
			const T	&operator*() const
			{
				return *_object;
			}

			///
			///@brief member dereferencer const operator
			///
			///
			const T	*operator->() const
			{
				return _object.get();
			}

		protected:
		private:
			std::shared_ptr<T>	_object;
	};
}


#endif /* !TASSET_HPP_ */
