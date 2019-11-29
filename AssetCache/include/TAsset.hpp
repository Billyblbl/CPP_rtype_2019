/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** TAsset
*/

#ifndef TASSET_HPP_
#define TASSET_HPP_

#include <functional>
#include <memory>
#include "AssetCache.hpp"

template<typename Component>
class TAsset {
	public:

		TAsset(const std::string &path):
			_asset(AssetCache::getGlobalCache().load<Component>(path))
		{}

		///
		///@brief object dereferencer operator
		///
		///
		Component	&operator*()
		{
			return *_asset;
		}

		///
		///@brief member dereferencer operator
		///
		///
		Component	*operator->()
		{
			return _asset.get();
		}

		///
		///@brief object dereferencer const operator
		///
		///
		const Component	&operator*() const
		{
			return *_asset;
		}

		///
		///@brief member dereferencer const operator
		///
		///
		const Component	*operator->() const
		{
			return _asset.get();
		}

		Component		*get()
		{
			return _asset.get();
		}

		const Component	*get() const
		{
			return _asset;
		}

	protected:
	private:
		std::shared_ptr<Component>	_asset;
};

#endif /* !TASSET_HPP_ */
