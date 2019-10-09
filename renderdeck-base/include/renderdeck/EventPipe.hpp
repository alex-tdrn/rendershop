#pragma once

#include "renderdeck/AbstractInputEventPort.hpp"
#include "renderdeck/OutputEventPort.hpp"

#include <unordered_map>
#include <cassert>

class EventPipe
{
private:
	mutable bool inputEventsRegistered = false;
	mutable std::unordered_map<std::string, AbstractInputEventPort> inputEvents;
	mutable bool outputEventsRegistered = false;
	mutable std::unordered_map<std::string, OutputEventPort> outputEvents;

public:
	EventPipe() = default;
	EventPipe(EventPipe const&) = delete;
	EventPipe(EventPipe&&) = delete;
	EventPipe& operator=(EventPipe const&) = delete;
	EventPipe& operator=(EventPipe&&) = delete;
	virtual ~EventPipe() = default;

public:
	virtual std::unordered_map<std::string, AbstractInputEventPort> registerInputEvents() const = 0;
	virtual std::unordered_map<std::string, OutputEventPort> registerOutputEvents() const = 0;

	AbstractInputEventPort const& getInputEventPorts(std::string name) const
	{
		if(!inputEventsRegistered)
		{
			inputEvents = registerInputEvents();
			inputEventsRegistered = true;
		}
		return inputEvents.at(name);
	}

	OutputEventPort const& getOutputEventPorts(std::string name) const
	{
		if(!outputEventsRegistered)
		{
			outputEvents = registerOutputEvents();
			outputEventsRegistered = true;
		}
		return outputEvents.at(name);
	}

};