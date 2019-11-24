/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Plugin
*/

#include "Plugin.hpp"

#if defined(_WIN32)
Plugin::Plugin(const std::string &path):
	_handle{LoadLibrary(path.c_str())}
{
	if (_handle == NULL)
		throw std::runtime_error(std::string(__func__) + " : " + GetLastError());
}
#else
Plugin::Plugin(const std::string &path):
	_handle{dlopen(path.c_str(), RTLD_NOW), [](void *hdl){
		auto	err = dlclose(hdl);
		if (err !=  0)
			throw std::runtime_error(std::string("dlclose : ") + dlerror());
	}}
{
	if (_handle == nullptr)
		throw std::runtime_error(std::string(__func__) + " : " + dlerror());
}
#endif


#if defined(_WIN32)
Plugin::~Plugin()
{
	if (_handle != NULL && FreeLibrary(_handle) == 0)
		throw std::runtime_error(std::string("FreeLibrary : ") + GetLastError());
}
#endif