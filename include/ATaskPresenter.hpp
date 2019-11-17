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

///
///@brief Base class for object presenting tasks to worker threads
///
///
class ATaskPresenter {
	public:

		///
		///@brief Destroy the ATaskPresenter object
		///
		///
		virtual ~ATaskPresenter() = default;

		///
		///@brief task check
		///
		///
		bool	hasAvailableTask() const;

		///
		///@brief ongoing task check
		///
		///
		bool	hasPendingTask() const;


		///
		///@brief get a task to execute and add it to the list of pending tasks
		///
		///
		TaskExecutor	&takeTask();

		///
		///@brief Notify the presenter that the task has been completed
		///
		///@param task completed task
		///
		void			reportTask(TaskExecutor task);


	protected:

		///
		///@brief Free for override event called from reporTask
		///
		///@param task 
		///
		virtual	void	onReportTask(TaskExecutor task) = 0;

		std::queue<TaskExecutor>	_available;
		std::vector<TaskExecutor>	_pending;
};

#endif /* !ATASKPRESENTER_HPP_ */
