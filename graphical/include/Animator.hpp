/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Animator
*/

#ifndef ANIMATOR_HPP_
#define ANIMATOR_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include "Timer.hpp"
#include "JSONValue.hpp"

class Animator {
	public:

		Animator(const JSONValue &params);

		using Frame = sf::IntRect;

		struct Animation {
			inline Animation(): duration(0) {}
			std::vector<Frame>	frames;
			Timer::Duration		duration;
		};

		const Animation &getCurrentAnimation() const;
		const Frame 	&getCurrentFrame() const;

		void			setAnimation(const std::string &state, const Timer::TimePoint &now);

		void			setFrame(const Timer::TimePoint &now);

		Animator		&operator++();
		Animator		&operator--();

		using AnimationVector = std::vector<std::pair<std::string, Animation>>;

		using iterator = AnimationVector::iterator;

	protected:
	private:
		AnimationVector		_anims;
		iterator			_current;
		Timer::TimePoint	_start;
		Frame				_currentFrame;

};

#endif /* !ANIMATOR_HPP_ */
