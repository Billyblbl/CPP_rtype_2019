/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** main
*/

#include <iostream>
#include "ComponentManager.hpp"
#include "TTask.hpp"
#include "SystemManager.hpp"
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
	SystemManager		sm;

	using type = zeofizoifjzo;
	m.addTable<type>();
	std::cout << m.getTable<type>().getTypeID().name() << std::endl;
	m.getTable<type>()->emplace_back(1, 2, 3.1);
	m.getTable<type>()->emplace_back(3, 4, 3.2);
	m.getTable<type>()->emplace_back(5, 6, 3.3);
	m.getTable<type>()->emplace_back(7, 8, 3.4);
	m.getTable<type>()->emplace_back(9, 10, 3.5);
	m.getTable<type>()->emplace_back(11, 12, 3.6);
	auto &pppp = m.getTable<type>().get()[0];
	std::cout << pppp->i << ' ' << pppp->e << ' '  << pppp->zeiouher << std::endl;


	TTask<type>	task(m.getTable<type>(), [](TComponentTable<zeofizoifjzo> &zbebs){
		for (auto &beb : zbebs.get()) {
			std::cout << beb->i << ' '  << beb->e << ' '  << beb->zeiouher << std::endl;
		}
	});

	TTask		task2(task);

	TTask		task3(std::move(task2));

	task();

	m.removeTable<type>();
	return 0;
}
