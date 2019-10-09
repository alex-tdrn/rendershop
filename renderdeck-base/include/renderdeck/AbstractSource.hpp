#pragma once

#include "renderdeck/AbstractPipe.hpp"
#include "renderdeck/Timestamp.hpp"
#include "renderdeck/EventPipe.hpp"
#include "renderdeck/InputEventPort.hpp"

#include <vector>

class AbstractDataPort;

class AbstractSource : public virtual AbstractPipe, public virtual EventPipe
{
protected:
	std::vector<AbstractDataPort*> abstractOutputDataPorts;
	mutable Timestamp timestamp;

public:
	AbstractSource() = default;
	AbstractSource(AbstractSource const&) = delete;
	AbstractSource(AbstractSource&&) = delete;
	AbstractSource& operator=(AbstractSource const&) = delete;
	AbstractSource& operator=(AbstractSource&&) = delete;
	virtual ~AbstractSource() = default;

	std::vector<AbstractDataPort*> const& getOutputDataPorts() const
	{
		return abstractOutputDataPorts;
	}

protected:
	bool isUpdateQueued() const
	{
		return timestamp.isReset();
	}

public:
	void queueUpdate()
	{
		timestamp.reset();
	}

	Timestamp const& getTimestamp() const
	{
		return timestamp;
	}

	std::unordered_map<std::string, std::unique_ptr<InputEventPort>> registerInputEvents() override
	{
		std::unordered_map<std::string, std::unique_ptr<InputEventPort>> inputEvents;
		inputEvents["Queue Update"] = InputEventPort::construct([this]() {
			queueUpdate();
		});
		return inputEvents;
	}

	std::unordered_map<std::string, OutputEventPort> registerOutputEvents() override
	{
		return {};
	}

	virtual void updateOutputsIfNeeded() const = 0;

};