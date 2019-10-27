#pragma once
#include <chrono>

template<typename T>
T lerp(T const& startValue, T const& endValue, float p)
{
	T difference = endValue - startValue;
	return startValue + p * difference;
}

template<typename T>
class Animation
{
private:
	bool playing = false;
	std::chrono::steady_clock::time_point startTime;

public:
	Animation() = default;
	Animation(Animation&&) = default;
	Animation(Animation const&) = default;
	Animation& operator=(Animation&&) = default;
	Animation& operator=(Animation const&) = default;
	~Animation() = default;

public:
	void play()
	{
		startTime = std::chrono::steady_clock::now();
		playing = true;
	}

	T get(T startValue, T endValue, std::chrono::milliseconds const& duration)
	{
		if(!playing)
			return endValue;
		auto const endTime = startTime + duration;
		auto const now = std::chrono::steady_clock::now();
		if(now > endTime)
		{
			playing = false;
			return endValue;
		}
		auto currentDuration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);

		float p = double(currentDuration.count()) / double(duration.count());

		return lerp(startValue, endValue, p);
	}

};