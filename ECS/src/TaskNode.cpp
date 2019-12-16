/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** task node object definition
*/

#include "TaskNode.hpp"

TaskNode::TaskNode(std::function<void()> &&func):
	_task(func)
{}

TaskNode::~TaskNode()
{
	for (auto *parent : _parentTasks)
		parent->removeChild(*this);
	for (auto *child: _childrenTasks)
		child->removeParent(*this);
}

void	TaskNode::operator()()
{
	_task();
}

TaskNode	&TaskNode::operator--()
{
	--_prerequisites;
	return *this;
}

void		TaskNode::resetPrerequisites()
{
	_prerequisites = _parentTasks.size();
}

int			TaskNode::getPrerequisites() const
{
	return _prerequisites;
}

void		TaskNode::addWriter(const std::type_index &writerType)
{
	_writerIDs.push_back(writerType);
	std::sort(_writerIDs.begin(), _writerIDs.end());
}

void		TaskNode::addReader(const std::type_index &readerType)
{
	_readerIDs.push_back(readerType);
	std::sort(_readerIDs.begin(), _readerIDs.end());
}

void		TaskNode::addParent(TaskNode &parent)
{
	_parentTasks.push_back(&parent);
	_prerequisites++;
}

void		TaskNode::removeParent(TaskNode &parent)
{
	_parentTasks.erase(std::find(_parentTasks.begin(), _parentTasks.end(), &parent));
	_prerequisites--;
}

void		TaskNode::linkParent(TaskNode &parent)
{
	addParent(parent);
	parent.addChild(*this);
}

void		TaskNode::unlinkParent(TaskNode &parent)
{
	removeParent(parent);
	parent.removeChild(*this);
}

TaskNode::Hierachy			&TaskNode::getParents()
{
	return _parentTasks;
}

const TaskNode::Hierachy	&TaskNode::getParents() const
{
	return _parentTasks;
}

void		TaskNode::addChild(TaskNode &child)
{
	_childrenTasks.push_back(&child);
}

void		TaskNode::removeChild(TaskNode &child)
{
	_childrenTasks.erase(std::find(_childrenTasks.begin(), _childrenTasks.end(), &child));
}

void		TaskNode::linkChild(TaskNode &child)
{
	addChild(child);
	child.addParent(*this);
}

void		TaskNode::unlinkChild(TaskNode &child)
{
	removeChild(child);
	child.removeParent(*this);
}

TaskNode::Hierachy			&TaskNode::getChildrens()
{
	return _childrenTasks;
}

const TaskNode::Hierachy	&TaskNode::getChildrens() const
{
	return _childrenTasks;
}

bool		TaskNode::operator==(const TaskNode &rhs) const
{
	return this == &rhs;
}

bool		TaskNode::operator<(const TaskNode &rhs) const
{
	return this < &rhs;
}

bool		TaskNode::isParallelisableWith(const TaskNode &other) const
{
	for (auto &id : other._writerIDs) {
		if (std::binary_search(_writerIDs.begin(), _writerIDs.end(), id)
			|| std::binary_search(_readerIDs.begin(), _readerIDs.end(), id)) {
			return false;
		}
	}
	for (auto &id : _writerIDs) {
		if (std::binary_search(other._readerIDs.begin(), other._readerIDs.end(), id))
			return false;
	}
	return true;
}
