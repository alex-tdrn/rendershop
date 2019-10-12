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
	EventPipe(EventPipe&&) = default;
	EventPipe& operator=(EventPipe const&) = delete;
	EventPipe& operator=(EventPipe&&) = default;
	virtual ~EventPipe() = default;

public:
	virtual void registerInputEvents() = 0;
	virtual void registerOutputEvents() = 0;

	template<typename F>
	void registerInputEvent(std::string name, F&& callable)
	{
		inputEvents[name] = std::make_unique<InputEventPort>(std::forward<F>(callable));
		inputEvents[name]->setName(name);
	}

	void registerOutputEvent(std::string name)
	{
		outputEvents[name] = OutputEventPort{};
		outputEvents[name].setName(name);
	}

	InputEventPort& getInputEventPort(std::string name)
	{
		if(!inputEventsRegistered)
		{
			registerInputEvents();
			inputEventsRegistered = true;
		}
		assert(inputEvents.find(name) != inputEvents.end());

		return *inputEvents[name];
	}

	OutputEventPort& getOutputEventPort(std::string name)
	{
		if(!outputEventsRegistered)
		{
			registerOutputEvents();
			outputEventsRegistered = true;
		}
		assert(outputEvents.find(name) != outputEvents.end());

		return outputEvents[name];
	}

};