#pragma once
#include "renderdeck/Sink.hpp"

#include <chrono>
#include <set>

class Timer : Sink<Timer, InputList<std::chrono::milliseconds>>
{
public:
	static inline std::string const name = registerPipe<Timer>("Timer");
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

private:
	mutable std::chrono::steady_clock::time_point nextActivationTime = std::chrono::steady_clock::time_point::max();

protected:
	void registerOutputEvents() override
	{
		AbstractSink::registerOutputEvents();
		registerOutputEvent("Timeout");
	}

	void update() const override
	{
		if(std::chrono::steady_clock::now() >= nextActivationTime)
		{
			//TODO
			const_cast<Timer*>(this)->getOutputEventPort("Timeout").trigger();
			nextActivationTime = std::chrono::steady_clock::now() + getInputDataPort<InputPorts::Interval>().getData();
		}
	}

};