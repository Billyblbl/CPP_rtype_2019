/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** rtype server
*/

#include <iostream>
#include <shared_mutex>
#include <mutex>
#include "Server.hpp"

int	main(int, char *av[])
{
	Server::io_service					service;
	Server::InstanceList				instances;
	std::vector<Server::InstanceIter>	stopped;

	std::shared_mutex					instancesMutex;

	Server	server(std::stoi(av[1]), service, instances);

	while (true) {
		if (instances.empty())
		// 	service.run_one();
		// else
			service.poll_one();

		if (!stopped.empty()){
			std::unique_lock	clearLock(instancesMutex);
			for (auto it : stopped)
				instances.erase(it);
			stopped.clear();
		}

		{
			std::shared_lock	processLock(instancesMutex);
			for (auto instance = instances.begin(); instance != instances.end(); instance++) {
				if (!instance->poll())
					stopped.push_back(instance);
			}
		}
	}
	return 0;
}