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
		// std::cout << '1' << std::endl;
		if (instances.empty())
			service.run_one();
		else
			service.poll_one();
		// std::cout << '2' << std::endl;
		for (auto &instance : instances) {
			// std::cout << '3' << std::endl;
			TaskExecutor	task = nullptr;
			{
				auto	lockedSched = *instance->scheduler;
				if (lockedSched->hasAvailableTask())
					task = lockedSched->takeTask();
			}
			// std::cout << '4' << std::endl;
			if (task != nullptr) {
				try {
					(*task)();
				} catch(const std::exception& e) {
					std::cerr << "Task Failed" << e.what() << '\n';
				}
				instance->scheduler->reportTask(task);
			}
			// std::cout << '5' << std::endl;
		}
		// std::cout << '6' << std::endl;
		//
	}
	return 0;
}