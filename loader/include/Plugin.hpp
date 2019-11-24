/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Plugin
*/

#ifndef PLUGIN_HPP_
#define PLUGIN_HPP_

#include <memory>
#include <functional>

#if defined(_WIN32)
	#include <windows.h> 
#else
	#include <dlfcn.h>
#endif

// move this to plugin interfaces thingy
// #if defined(_WIN32)
//   // MS Windows DLLs (*.dll)
//   #define PLUGIN_VISIBLE __declspec(dllexport)
// #else
//   // Unix-like Shared Object (.so) operating systems and GCC.
//   #define PLUGIN_VISIBLE __attribute__ ((visibility ("default")))
// #endif

class Plugin {
	public:

		Plugin(const std::string &path);

#if defined(_WIN32)
		~Plugin();
#else
		~Plugin() = default;
#endif

		//FARPROC returned by windows' GetProcAddr and its fuckeries of
		// non compatible pointer types means that we have no guarantes
		// that we can use those like we'd do on linux, so no windows
		// version for now
		// TODO Find and implement a windows way to do this

		template<typename T>
		T		&getFromSymbol(const std::string &key)
		{
			dlerror();
			auto	*thing = dlsym(_handle.get(), key.c_str());
			auto	*err = dlerror();
			if (err != nullptr)
				throw std::runtime_error(std::string(__func__) + " : " + err);
			T		&cast = dynamic_cast<T &>(thing);
			return cast;
		}

		template<typename Callable, typename... Args>
		auto	callFromSymbol(const std::string &key, Args&&... args)
		{
			dlerror();
			auto	*thing = dlsym(_handle.get(), key.c_str());
			auto	*err = dlerror();
			if (err != nullptr)
				throw std::runtime_error(std::string(__func__) + " : " + err);
			return Callable(thing)(std::forward<Args>(args)...);
		}

	protected:
	private:

#if defined(_WIN32)
		HINSTANCE	_handle;
#else
		std::unique_ptr<void, std::function<void(void *)>>	_handle;
#endif

};

#endif /* !PLUGIN_HPP_ */
