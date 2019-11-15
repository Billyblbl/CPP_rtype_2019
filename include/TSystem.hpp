/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** ECS system template
*/

#ifndef TSYSTEM_HPP_
#define TSYSTEM_HPP_

#include <tuple>
#include "ISystem.hpp"
#include "TComponentTable.hpp"

///
///@brief ECS System Template
///
///@tparam Components Component types accessed by the system
///
template<typename... Components>
class TSystem : public ISystem {
	public:

		///
		///@brief Reload the system
		///
		///
		void	reload()
		{
			onReload();
		}

		///
		///@brief Free for override event triggered on call to reload
		///
		///
		virtual void	onReload() {}

		///
		///@brief interna tuple types of references to managed components' tables
		///
		///
		using TablePacket = std::tuple<TComponentTable<Components> &...>;


	protected:
	private:

		std::tuple<TComponentTable<ComponentT>...>	_componentsTables;
};

#endif /* !TSYSTEM_HPP_ */
