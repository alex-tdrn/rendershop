#pragma once
#include "renderdeck/AbstractPipeline.hpp"

#include <chrono>
#include <set>

class Timer
{
private:
	std::chrono::steady_clock::time_point nextActivationTime = std::chrono::steady_clock::time_point::max();
	std::chrono::milliseconds interval{1'000};
	std::set<AbstractSource*> sources;
	std::set<AbstractSink*> sinks;

private:
	void updateActivationTime()
	{
		nextActivationTime = std::chrono::steady_clock::now() + interval;
	}

public:
	void setInterval(std::chrono::milliseconds interval)
	{
		this->interval = interval;
		updateActivationTime();
	}

	void addSource(AbstractSource* source)
	{
		sources.insert(source);
	}

	void addSink(AbstractSink* sink)
	{
		sinks.insert(sink);
	}

	void poll()
	{
		if(std::chrono::steady_clock::now() >= nextActivationTime)
		{
			for(auto* source : sources)
				source->queueUpdate();
			for(auto* sink : sinks)
				sink->trigger();
			updateActivationTime();
		}
	}
};