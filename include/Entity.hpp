/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** ECS Entity declaration
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <mutex>
#include <unordered_map>
#include <memory>
#include <tuple>
#include "TComponent.hpp"

class Entity {
	public:

		void	lock();
		void	unlock();

#pragma region getters

		template<typename Object>
		auto	&getComponent()
		{
			using Component = TComponent<Object>;
			return *static_cast<Component *>(_components.at(Component::getID()).get());
		}

		template<typename... Objects>
		auto	&getComponents()
		{
			return std::tie(getComponent<Objects>()...);
		}

		template<typename Object>
		const auto	&getComponent() const
		{
			using Component = TComponent<Object>;
			return *static_cast<Component *>(_components.at(Component::getID()).get());
		}

		template<typename... Objects>
		const auto	&getComponents() const
		{
			return std::tie(getComponent<Objects>()...);
		}

#pragma endregion getters

#pragma region adders

		template<typename Object, typename... Args>
		void		addComponent(Args&&... args)
		{
			using Component = TComponent<Object>;
			std::lock_guard	lock(_mutex);
			_components.emplace(Component::getID(), std::make_unique<Component>(std::forward<Args>(args)...));
		}

		template<typename Object, typename... Args>
		void		addComponentByTuple(std::tuple<Args...> &&args)
		{
			using tupleT = std::tuple<Args...>;
			std::apply(&Entity::addComponent<Object, Args...>, std::tuple_cat(std::make_tuple(this), std::forward<tupleT>(args)));
		}

		template<typename... Objects, typename... ArgsTuples>
		void		addComponents(ArgsTuples&&... args)
		{
			(addComponentByTuple<Objects>(std::forward<ArgsTuples>(args)), ...);
		}


#pragma endregion adders

#pragma region removers

		template<typename Object>
		void		removeComponent()
		{
			using Component = TComponent<Object>;
			std::lock_guard	lock(_mutex);
			_components.erase(Component::getID());
		}

		template<typename... Objects>
		void		removeComponents()
		{
			(removeComponent<Objects>(), ...);
		}

#pragma endregion removers

#pragma region checks

		template<typename Object>
		bool		hasComponent()
		{
			using Component = TComponent<Object>;
			return _components.find(Component::getID()) != _components.end();
		}

		template<typename... Objects>
		bool		hasComponentsAll()
		{
			return (hasComponent<Objects>() && ...);
		}

		template<typename... Objects>
		bool		hasComponentsAny()
		{
			return (hasComponent<Objects>() || ...);
		}

#pragma endregion checks

	private:

	using UniqueComponent = std::unique_ptr<IComponent>;
	using ComponentMap = std::unordered_map<TypeIndex, UniqueComponent>;

	ComponentMap	_components;
	std::mutex		_mutex;
};

#endif /* !ENTITY_HPP_ */
