/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** New event model template
*/

#ifndef TEVENT_HPP_
#define TEVENT_HPP_

#include <queue>

template<typename DataType>
class TEvent {
	public:

		void	trigger(DataType &&trigger)
		{
			_triggered.push(trigger);
		}

		size_t	getSize() const
		{
			return _triggered.size();
		}

		bool	isEmpty() const
		{
			return _triggered.empty();
		}

		const DataType	&front() const
		{
			return _triggered.front();
		}

		DataType	&front()
		{
			return _triggered.front();
		}

		void	consume()
		{
			_triggered.pop();
		}

	protected:
	private:
		std::queue<DataType>	_triggered;

};

#endif /* !TEVENT_HPP_ */
