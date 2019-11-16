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

class Scheduler : public ATaskPresenter {
	public:

	Scheduler();

	//yes this is a list, we don't need efficient iteration as the only iterative operations
	// done on this will be the reset of prerequisites at frame beginnings, but we do need
	// pointers stability & easy insertion/deletion
	using Graph = std::list<TaskNode>;

	void	onReportTask(TaskExecutor task) override;
	void	onFrameBegin();
	void	onFrameEnd();

	template<typename... Components>
	auto	&postTask(const TTask<Components...> &task)
	{
		auto &newNode = _taskgraph.emplace_back(task);
		(..., [](Components *ignore = nullptr){
			if constexpr (!std::is_const_v<std::remove_reference_t<Components>>) {
				newNode.addMutator(typeid(Components));
			}
		}());
		newNode.linkParent(_beginNode);
		newNode.linkChild(_endNode);
		for (auto &node : _taskgraph) {
			if (!node.isParallelisableWith(newNode))
				node.linkChild(newNode);
		}
		newNode.resetPrerequisites();
		return newNode;
	}

	void	removeTask(TaskNode &node);

	protected:
	private:

		Graph		_taskgraph;
		TaskNode	_beginNode;
		TaskNode	_endNode;

};

#endif /* !SCHEDULER_HPP_ */
