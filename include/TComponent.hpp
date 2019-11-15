/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** ECS component template
*/

#ifndef TCOMPONENT_HPP_
#define TCOMPONENT_HPP_

#include <cinttypes>

using EntityID = uint64_t;

template<typename ObjectT>
class TComponent {
	public:

		using Object = ObjectT;

		template<typename... Args>
		TComponent(Args&&... args):
			_obj(std::forward<Args>(args)...)
		{}

		operator Object &()
		{
			return _obj;
		}

		operator const Object &() const
		{
			return _obj;
		}

		Object			&operator*()
		{
			return _obj;
		}

		const Object	&operator*() const
		{
			return _obj;
		}

		Object			*operator->()
		{
			return &_obj;
		}

		const Object	*operator->() const
		{
			return &_obj;
		}

	protected:
	private:

	Object		_obj;
	EntityID	_parent;
};

#endif /* !TCOMPONENT_HPP_ */
