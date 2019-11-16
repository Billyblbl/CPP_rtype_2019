/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** main
*/

#include <iostream>
#include "ComponentManager.hpp"
#include "TTask.hpp"
#include "Scheduler.hpp"
#include "Instance.hpp"

struct zeofizoifjzo {
	zeofizoifjzo(int a, int b, double c):
		i(a),
		e(b),
		zeiouher(c)
	{}

	int 	i;
	int 	e;
	double	zeiouher;
};

int	main(int, char *[])
{

	Instance	instance;

	using type = zeofizoifjzo;
	instance.components.addTable<type>();
	instance.components.addTable<int>();
	TTask<const int>	t(instance.components.getTable<int>(), [](auto &){
		std::cout << "lolilol" << std::endl;
	});

	//scheduler tests
	auto & node = instance.scheduler.postTask(t);

	for (int i = 0; i < 6; ++i) {
		if (instance.scheduler.hasAvailableTask()) {
			auto *ta = instance.scheduler.takeTask();
			(*ta)();
			instance.scheduler.reportTask(ta);
		}
	}

	//table manipulation tests
	std::cout << instance.components.getTable<type>().getTypeID().name() << std::endl;
	instance.components.getTable<type>()->emplace_back(1, 2, 3.1);
	instance.components.getTable<type>()->emplace_back(3, 4, 3.2);
	instance.components.getTable<type>()->emplace_back(5, 6, 3.3);
	instance.components.getTable<type>()->emplace_back(7, 8, 3.4);
	instance.components.getTable<type>()->emplace_back(9, 10, 3.5);
	instance.components.getTable<type>()->emplace_back(11, 12, 3.6);
	auto &pppp = instance.components.getTable<type>().get()[0];
	std::cout << pppp->i << ' ' << pppp->e << ' '  << pppp->zeiouher << std::endl;


	//task behavior test
	TTask<type>	task(instance.components.getTable<type>(), [](TComponentTable<type> &zbebs){
		for (auto &beb : zbebs.get()) {
			std::cout << beb->i << ' '  << beb->e << ' '  << beb->zeiouher << std::endl;
		}
	});

	TTask		task2(task);

	TTask		task3(std::move(task2));

	task();

	instance.scheduler.removeTask(node);

	instance.components.removeTable<type>();
	return 0;
}
