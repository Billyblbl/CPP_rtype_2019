/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Animator
*/

#include <iostream>
#include "Animator.hpp"
#include "Component.hpp"

Animator::Animator(const JSONValue &params)
{
	try {
		for (auto &animationData : params) {
			auto &[_, anim] = _anims.emplace_back(animationData["state"].get<JSONValue::String>(), Animation{});
			std::chrono::duration<double> seconds(animationData["duration"].get<JSONValue::Numberf>());
			anim.duration = std::chrono::duration_cast<Timer::Duration>(seconds);
			for (auto &frameData : animationData["frames"]) {
				sf::Vector2i	upLeft(
					frameData["ULx"].get<JSONValue::Numberi>(),
					frameData["ULy"].get<JSONValue::Numberi>()
				);
				sf::Vector2i	downRight(
					frameData["DRx"].get<JSONValue::Numberi>(),
					frameData["DRy"].get<JSONValue::Numberi>()
				);
				anim.frames.emplace_back(upLeft, downRight - upLeft);
			}
		}
	} catch(const std::exception& e) {
		std::cerr << __func__ << " : " << e.what() << '\n';
		throw;
	}
	setAnimation(_anims.front().first, Timer::Clock::now());
}

const Animator::Animation	&Animator::getCurrentAnimation() const
{
	return _current->second;
}

const Animator::Frame		&Animator::getCurrentFrame() const
{
	return _currentFrame;
}

void	Animator::setAnimation(const std::string &state, const Timer::TimePoint &now)
{
	_start = now;
	_current = std::find_if(_anims.begin(), _anims.end(), [&](auto &pair){
		return state == pair.first;
	});
	setFrame(_start);
}

void	Animator::setFrame(const Timer::TimePoint &now)
{
	auto idx = _current->second.frames.size() * (now - _start) / _current->second.duration;
	_currentFrame = _current->second.frames[idx % _current->second.frames.size()];
}

