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
	_endNode([this](){onFrameEnd();}),
	_running(true)
{
	_endNode.linkChild(_beginNode);
	_endNode.linkParent(_beginNode);
	_available.push(&_beginNode);
}

Scheduler::~Scheduler()
{
	for (auto &node : _taskgraph) {
		node.unlinkParent(_beginNode);
		node.unlinkChild(_endNode);
	}
	_endNode.unlinkChild(_beginNode);
	_endNode.unlinkParent(_beginNode);
	// _taskgraph.clear();
}

void	Scheduler::onReportTask(TaskExecutor task)
{
	if (_running) {
		for (auto *it : task->getChildrens()) {
			auto &node = *it;
			--node;
			if (node.getPrerequisites() == 0)
				_available.push(&node);
		}
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
	// if (!_running) {
		// while (!_available.empty()) {
		// 	_available.pop();
		// }
	// }
	// std::cout << __func__ << std::endl;
}

void	Scheduler::removeTask(TaskNode &node)
{
	_taskgraph.remove(node);
}

void	Scheduler::stop()
{
	_running = false;
}