/*
** EPITECH PROJECT, 2019
** RTYPE
** File description:
** abstract task presenter base class definition
*/

#include <algorithm>
#include "ATaskPresenter.hpp"

bool			ATaskPresenter::hasAvailableTask() const
{
	return !_available.empty();
}

bool			ATaskPresenter::hasPendingTask() const
{
	return !_pending.empty();
}

TaskExecutor	&ATaskPresenter::takeTask()
{
	_pending.push_back(_available.front());;
	_available.pop();
	return _pending.back();
}

void			ATaskPresenter::reportTask(TaskExecutor task)
{
	auto	it = std::find(_pending.begin(), _pending.end(), task);
	auto	taskNode = *it;
	_pending.erase(it);
	onReportTask(taskNode);
}
