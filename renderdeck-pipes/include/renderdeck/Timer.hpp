#pragma once
#include "renderdeck/Sink.hpp"

#include <chrono>
#include <array>

using namespace std::chrono_literals;

class Timer : public Sink<Timer, InputList<std::chrono::milliseconds>>
{
public:
	struct InputPorts
	{
		static inline std::array names = {
			"Interval"
		};
		enum
		{
			Interval
		};
	};

public:
	static inline std::string const name = registerPipe<Timer>("Timer");

private:
	mutable std::chrono::steady_clock::time_point nextActivationTime = std::chrono::steady_clock::now() + 1'000ms;

protected:
	void registerOutputEvents() override;

public:
	void update() override;

};