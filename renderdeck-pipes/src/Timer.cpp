#include "renderdeck\Timer.hpp"

void Timer::registerOutputEvents()
{
	AbstractSink::registerOutputEvents();
	registerOutputEvent("Timeout");
}

void Timer::update()
{
	if(std::chrono::steady_clock::now() >= nextActivationTime)
	{
		trigger("Timeout");
		nextActivationTime = std::chrono::steady_clock::now() + 1'000ms;//getInputDataPort<InputPorts::Interval>().getData();
	}
}