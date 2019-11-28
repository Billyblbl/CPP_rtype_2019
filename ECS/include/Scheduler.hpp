/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** instance scheduler
*/

#ifndef SCHEDULER_HPP_
#define SCHEDULER_HPP_

// #include <unordered_set>
#include <type_traits>
#include <list>
#include "ATaskPresenter.hpp"
#include "TTask.hpp"
#include "TaskNode.hpp"

///
///@brief Instance task scheduer object
///
///
class Scheduler : public ATaskPresenter {
	public:

	///
	///@brief Construct a new Scheduler object
	///
	///
	Scheduler();

	///
	///@brief Task Graph container
	///
	/// yes this is a list, we don't need efficient iteration as the only iterative operations
	/// done on this will be the reset of prerequisites at frame beginnings, but we do need
	/// pointers stability & easy insertion/deletion
	///
	using Graph = std::list<TaskNode>;

	///
	///@brief Event reaction once a task has been completed
	///
	///@param task completed task
	///
	void	onReportTask(TaskExecutor task) override;

	///
	///@brief Internal task associated with the begining of a simulation frame
	///
	///
	void	onFrameBegin();

	///
	///@brief Internal task associated with the end of a simulation frame
	///
	///
	void	onFrameEnd();

	///
	///@brief Adds a new task in the taskgraph
	///
	/// Properly connect the constructed node depending on parallelisation possibilities
	///
	///@tparam Components used by the task, non-const are considered writers and can't be parallelized with other writers of the same type
	///@param task to add a ndoe with
	///
	template<typename... Components>
	auto	&postTask(const ECS::TTask<Components...> &task)
	{
		auto &newNode = _taskgraph.emplace_back(task);
		(..., [&newNode](Components *ignore = nullptr){
			using Comp = std::remove_reference_t<Components>;
			if constexpr (!std::is_const_v<Comp>) {
				newNode.addWriter(typeid(std::remove_const_t<Comp>));
			} else {
				newNode.addReader(typeid(std::remove_const_t<Comp>));
			}
		}());
		newNode.linkParent(_beginNode);
		newNode.linkChild(_endNode);
		for (auto &node : _taskgraph) {
			if (&newNode != &node && !node.isParallelisableWith(newNode))
				node.linkChild(newNode);
		}
		newNode.resetPrerequisites();
		return newNode;
	}

	///
	///@brief Removes a task from the taskGraph
	///
	///@param node 
	///
	void	removeTask(TaskNode &node);

	protected:
	private:

		Graph		_taskgraph;
		TaskNode	_beginNode;
		TaskNode	_endNode;

};

#endif /* !SCHEDULER_HPP_ */
