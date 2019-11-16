/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Task node object class
*/

#ifndef TASKNODE_HPP_
#define TASKNODE_HPP_

#include <functional>
#include <vector>
#include <typeindex>

class TaskNode {
	public:

		using Hierachy = std::vector<TaskNode *>;

		TaskNode(std::function<void()> &&func);

		template<typename... TypeIds>
		TaskNode(std::function<void()> &&func, TypeIds&&... mutators):
			_task(func),
			_mutatorIDs({std::forward<TypeIds>(mutators)...})
		{}

		~TaskNode();

		void		operator()();

		TaskNode	&operator--();
		void		resetPrerequisites();
		int			getPrerequisites() const;

		void		addMutator(const std::type_index &mutatorType);

		void		addParent(TaskNode &parent);
		void		removeParent(TaskNode &parent);
		void		linkParent(TaskNode &parent);
		void		unlinkParent(TaskNode &parent);
		Hierachy		&getParents();
		const Hierachy	&getParents() const;

		void		addChild(TaskNode &child);
		void		removeChild(TaskNode &child);
		void		linkChild(TaskNode &child);
		void		unlinkChild(TaskNode &child);
		Hierachy		&getChildrens();
		const Hierachy	&getChildrens() const;

		bool		operator==(const TaskNode &rhs) const;
		bool		operator<(const TaskNode &rhs) const;

		bool		isParallelisableWith(const TaskNode &other) const;

	protected:
	private:

		std::function<void()>			_task;
		std::vector<std::type_index>	_mutatorIDs;
		Hierachy						_parentTasks;
		Hierachy						_childrenTasks;
		int								_prerequisites;
};

#endif /* !TASKNODE_HPP_ */
