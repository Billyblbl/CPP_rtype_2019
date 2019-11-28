/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** instance bound plugin manager
*/

#ifndef PLUGINMANAGER_HPP_
#define PLUGINMANAGER_HPP_

#include <unordered_map>
#include <string>
#include <memory>
#include "Plugin.hpp"

class PluginManager {
	public:

		Plugin			&load(const std::string &path);
		void			unload(const std::string &path);
		void			clear();

		Plugin			&operator[](const std::string &key);
		const Plugin	&operator[](const std::string &key) const;


	protected:
	private:

		using PluginMap = std::unordered_map<std::string, std::shared_ptr<Plugin>>;

		PluginMap	_plugins;
};

#endif /* !PLUGINMANAGER_HPP_ */
