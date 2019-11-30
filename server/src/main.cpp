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
	Server	server(std::stoi(av[1]), service, instances);
	while (true) {
		//make this the thread loop
		service.poll();
		for (auto &instance : instances) {
			TaskExecutor	task = nullptr;
			{
				auto	lockedSched = *instance->scheduler;
				if (lockedSched->hasAvailableTask())
					task = lockedSched->takeTask();
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