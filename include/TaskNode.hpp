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

///
///@brief Task Node representation for task graph
///
///
class TaskNode {
	public:

		///
		///@brief Node connection collection type
		///
		///
		using Hierachy = std::vector<TaskNode *>;

		///
		///@brief Construct a new Task Node object
		///
		///@param func callable used as the execution function of the task
		///
		TaskNode(std::function<void()> &&func);

		///
		///@brief Construct a new Task Node object with mutators
		///
		///
		template<typename... TypeIds>
		TaskNode(std::function<void()> &&func, TypeIds&&... mutators):
			_task(func),
			_mutatorIDs({std::forward<TypeIds>(mutators)...})
		{}

		///
		///@brief Destroy the Task Node object
		///
		///
		~TaskNode();

		///
		///@brief call operator, executes the task
		///
		///
		void		operator()();

		///
		///@brief Decrement operator, decrement the prerequisites counter
		///
		///
		TaskNode	&operator--();

		///
		///@brief Reset the prerequisites counter to the number of parent tasks
		///
		///
		void		resetPrerequisites();

		///
		///@brief Get the Prerequisites count
		///
		///
		int			getPrerequisites() const;

		///
		///@brief Adds a mutator type index to the node
		///
		///@param mutatorType type index of the writer type of the mutator
		///
		void		addMutator(const std::type_index &mutatorType);

		///
		///@brief Adds a parent node to this
		///
		///
		void		addParent(TaskNode &parent);

		///
		///@brief Removes a parent node from this
		///
		///
		void		removeParent(TaskNode &parent);

		///
		///@brief Links a node as the parent of this, and this as a child of the node
		///
		///
		void		linkParent(TaskNode &parent);

		///
		///@brief Unlinks a parent node both ways
		///
		///
		void		unlinkParent(TaskNode &parent);

		///
		///@brief Get the Parent nodes
		///
		///
		Hierachy		&getParents();

		///
		///@brief Get the Parent nodes
		///
		///
		const Hierachy	&getParents() const;

		///
		///@brief Adds a child node to this
		///
		///
		void		addChild(TaskNode &child);

		///
		///@brief Removes a child node from this
		///
		///
		void		removeChild(TaskNode &child);

		///
		///@brief Links a node as the child of this, and this as a parent of the node
		///
		///
		void		linkChild(TaskNode &child);

		///
		///@brief Unlinks a child node both ways
		///
		///
		void		unlinkChild(TaskNode &child);

		///
		///@brief Get the Children nodes
		///
		///
		Hierachy		&getChildrens();


		///
		///@brief Get the Children nodes
		///
		///
		const Hierachy	&getChildrens() const;

		///
		///@brief Equality operator
		///
		///
		bool		operator==(const TaskNode &rhs) const;

		///
		///@brief Inferiority operator
		///
		///
		bool		operator<(const TaskNode &rhs) const;

		///
		///@brief Parallelisability check
		///
		///
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
