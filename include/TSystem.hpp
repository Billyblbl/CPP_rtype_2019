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

template<typename... Components>
class TSystem : public ISystem {
	public:
		TSystem();
		~TSystem();

		void	reload()
		{
			onReload();
		}

		virtual void	onReload() {}

		using TablePacket = std::tuple<TComponentTable<Components> &...>;


	protected:
	private:

		std::tuple<TComponentTable<ComponentT>...>	_componentsTables;
};

#endif /* !TSYSTEM_HPP_ */
