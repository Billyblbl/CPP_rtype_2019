/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** type presenter abstract object
*/

#ifndef ATASKPRESENTER_HPP_
#define ATASKPRESENTER_HPP_

#include <functional>
#include <queue>
#include <vector>

#include "TaskNode.hpp"

//tmp
using TaskExecutor = TaskNode *;

class ATaskPresenter {
	public:

		virtual ~ATaskPresenter() = default;

		bool	hasAvailableTask() const;
		bool	hasPendingTask() const;

		TaskExecutor	&takeTask();
		void			reportTask(TaskExecutor task);

		virtual	void	onReportTask(TaskExecutor task) = 0;

	protected:
		std::queue<TaskExecutor>	_available;
		std::vector<TaskExecutor>	_pending;
};

#endif /* !ATASKPRESENTER_HPP_ */
