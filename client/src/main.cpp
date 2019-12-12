/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** rtype client
*/
// #include "Renderer.hpp"
#include "Instance.hpp"
#include "AssetCache.hpp"

#include <iostream>
#include "Client.hpp"

int	main(int, char *av[])
{
	Client::io_service	service;
	Client::io_service::work	work(service);
	Instance			instance(av[1]);
	Client				client(service, instance);
	client.connect(std::string(av[1]), std::stoi(av[2]));
	std::cout << "connected" << std::endl;
	client.makeInstance(std::string(av[3]));
	std::cout << "requested instance" << std::endl;
	while (true) {
		//make this the thread loop
		// std::cout << "loopin" << std::endl;
		service.poll();
		TaskExecutor	task = nullptr;
		{
			auto	lockedSched = *instance.scheduler;
			if (lockedSched->hasAvailableTask())
				task = lockedSched->takeTask();
		}
		if (task != nullptr) {
			try {
				(*task)();
			} catch(const std::exception& e) {
				std::cerr << "Task Failed" << e.what() << '\n';
			}
			instance.scheduler->reportTask(task);
		}
		//
	}
	return 0;
}