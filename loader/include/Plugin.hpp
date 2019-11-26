/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Plugin
*/

#ifndef PLUGIN_HPP_
#define PLUGIN_HPP_

#include <functional>

	#if defined(_WIN32)
		#include <windows.h> 

class Plugin {
	public:

		Plugin(const std::string &path);

		template<typename Callable = long(), typename... Args>
		auto	call(const std::string &key, Args&&... args)
		{
			auto	thing = GetProcAddress(_handle, key);
			if (thing == NULL)
				throw std::runtime_error(std::string(__func__) + " : " + GetLastError());
			return std::function<Callable>(thing)(std::forward<Args>(args)...);
		}

		~Plugin();

	protected:
	private:


	HINSTANCE	_handle;

};

	#else
		#include <memory>
		#include <dlfcn.h>

class Plugin {
	public:

		Plugin(const std::string &path);

		~Plugin() = default;

		template<typename Callable = long(), typename... Args>
		auto	call(const std::string &key, Args&&... args)
		{
			using Functional = std::function<Callable>;
			using FctPtr = FunctionalTarget<Callable>;
			dlerror();
			auto	*thing = dlsym(_handle.get(), key.c_str());
			auto	*err = dlerror();
			if (err != nullptr)
				throw std::runtime_error(std::string(__func__) + " : " + err);
			Functional	callable(reinterpret_cast<FctPtr>(thing));
			return callable(std::forward<Args>(args)...);
		}

		template<typename Callable = long()>
		auto	get(const std::string &key)
		{
			using Functional = std::function<Callable>;
			using FctPtr = FunctionalTarget<Callable>;
			dlerror();
			auto	*thing = dlsym(_handle.get(), key.c_str());
			auto	*err = dlerror();
			if (err != nullptr)
				throw std::runtime_error(std::string(__func__) + " : " + err);
			return Functional(reinterpret_cast<FctPtr>(thing));
		}

	protected:
	private:

		template<typename T>
		struct FunctionalTraits {};

		template<typename R, typename... Args>
		struct FunctionalTraits<std::function<R(Args...)>> {
			using resultType = R;
			using signature = R(*)(Args...);
			struct argumentTypes {
				using asTuple = std::tuple<Args...>;

				template<size_t index>
				using arg = std::tuple_element_t<index, asTuple>;
			};
		};

		template<typename Callable>
		using FunctionalTarget = typename FunctionalTraits<std::function<Callable>>::signature;

		std::unique_ptr<void, std::function<void(void *)>>	_handle;

};



	#endif /* !OS check */
#endif /* !PLUGIN_HPP_ */

// move this to plugin interfaces thingy
// #if defined(_WIN32)
//   // MS Windows DLLs (*.dll)
//   #define PLUGIN_VISIBLE __declspec(dllexport)
// #else
//   // Unix-like Shared Object (.so) operating systems and GCC.
//   #define PLUGIN_VISIBLE __attribute__ ((visibility ("default")))
// #endif

