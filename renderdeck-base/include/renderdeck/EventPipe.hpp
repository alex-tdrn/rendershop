#pragma once

#include "renderdeck/OutputEventPort.hpp"
#include "renderdeck/InputEventPort.hpp"

#include <unordered_map>
#include <cassert>
#include <memory>

class EventPipe
{
private:
	mutable bool inputEventsRegistered = false;
	mutable std::unordered_map<std::string, std::unique_ptr<InputEventPort>> inputEvents;
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
	virtual std::unordered_map<std::string, std::unique_ptr<InputEventPort>> registerInputEvents() = 0;
	virtual std::unordered_map<std::string, OutputEventPort> registerOutputEvents() = 0;

	InputEventPort& getInputEventPort(std::string name)
	{
		if(!inputEventsRegistered)
		{
			inputEvents = registerInputEvents();
			inputEventsRegistered = true;
		}
		assert(inputEvents.find(name) != inputEvents.end());

		return *inputEvents[name];
	}

	OutputEventPort& getOutputEventPort(std::string name)
	{
		if(!outputEventsRegistered)
		{
			outputEvents = registerOutputEvents();
			outputEventsRegistered = true;
		}
		assert(outputEvents.find(name) != outputEvents.end());

		return outputEvents[name];
	}

};