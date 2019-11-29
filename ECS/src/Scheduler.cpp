/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** scheduler object definition
*/

#include "Scheduler.hpp"

//tmp
#include <iostream>

Scheduler::Scheduler():
	_beginNode([this](){onFrameBegin();}),
	_endNode([this](){onFrameEnd();})
{
	_endNode.linkChild(_beginNode);
	_endNode.linkParent(_beginNode);
	_available.push(&_beginNode);
}


void	Scheduler::onReportTask(TaskExecutor task)
{
	for (auto *it : task->getChildrens()) {
		auto &node = *it;
		--node;
		if (node.getPrerequisites() == 0)
			_available.push(&node);
	}
}

void	Scheduler::onFrameBegin()
{
	// std::cout << __func__ << std::endl;
	for (auto &node : _taskgraph) {
		node.resetPrerequisites();
	}
	_beginNode.resetPrerequisites();
	_endNode.resetPrerequisites();
}

void	Scheduler::onFrameEnd()
{
	// std::cout << __func__ << std::endl;
}

void	Scheduler::removeTask(TaskNode &node)
{
	_taskgraph.remove(node);
}