/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** New event model template
*/

#ifndef TEVENT_HPP_
#define TEVENT_HPP_

#include <vector>

template<typename DataType>
class TEvent {
	public:

		void	enqueue(DataType &&eventData)
		{
			_enqueued.push_back(eventData);
		}

		size_t	getSize() const
		{
			return _enqueued.size();
		}

		bool	isEmpty() const
		{
			return _enqueued.empty();
		}

		void	clear()
		{
			_enqueued.clear();
		}

		decltype(auto)	begin()
		{
			return _enqueued.begin();
		}

		decltype(auto)	end()
		{
			return _enqueued.end();
		}

		decltype(auto)	begin() const
		{
			return _enqueued.begin();
		}

		decltype(auto)	end() const
		{
			return _enqueued.end();
		}

	protected:
	private:
		std::vector<DataType>	_enqueued;

};

#endif /* !TEVENT_HPP_ */
