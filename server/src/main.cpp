/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** rtype server
*/

#include <iostream>
#include "Server.hpp"

int	main(int, char *av[])
{
	Server::io_service		service;
	Server::InstanceList	instances;
	Server	server(std::atoi(av[1]), service, instances);
	while (true) {
		//make this the thread loop
		for (auto &instance : instances) {
			TaskExecutor	task = nullptr;
			{
				service.poll();
				auto	lockedSched = *instance->scheduler;
				if (lockedSched->hasAvailableTask())
					task = instance->scheduler->takeTask();
			}
			if (task != nullptr) {
				try {
					(*task)();
				} catch(const std::exception& e) {
					std::cerr << "Task Failed" << e.what() << '\n';
				}
				instance->scheduler->reportTask(task);
			}
		}
		//
	}
	return 0;
}