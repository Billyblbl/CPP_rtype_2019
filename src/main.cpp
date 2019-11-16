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
	ComponentManager	m;
	Scheduler			s;

	using type = zeofizoifjzo;
	m.addTable<type>();
	m.addTable<int>();
	TTask<const int>	t(m.getTable<int>(), [](auto &){
		std::cout << "lolilol" << std::endl;
	});

	//scheduler tests
	auto & node = s.postTask(t);

	for (int i = 0; i < 6; ++i) {
		if (s.hasAvailableTask()) {
			auto *ta = s.takeTask();
			(*ta)();
			s.reportTask(ta);
		}
	}

	//table manipulation tests
	std::cout << m.getTable<type>().getTypeID().name() << std::endl;
	m.getTable<type>()->emplace_back(1, 2, 3.1);
	m.getTable<type>()->emplace_back(3, 4, 3.2);
	m.getTable<type>()->emplace_back(5, 6, 3.3);
	m.getTable<type>()->emplace_back(7, 8, 3.4);
	m.getTable<type>()->emplace_back(9, 10, 3.5);
	m.getTable<type>()->emplace_back(11, 12, 3.6);
	auto &pppp = m.getTable<type>().get()[0];
	std::cout << pppp->i << ' ' << pppp->e << ' '  << pppp->zeiouher << std::endl;


	//task behavior test
	TTask<type>	task(m.getTable<type>(), [](TComponentTable<type> &zbebs){
		for (auto &beb : zbebs.get()) {
			std::cout << beb->i << ' '  << beb->e << ' '  << beb->zeiouher << std::endl;
		}
	});

	task();

	s.removeTask(node);

	m.removeTable<type>();
	return 0;
}
