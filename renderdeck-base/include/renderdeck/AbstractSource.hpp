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
	AbstractSource(AbstractSource&&) = default;
	AbstractSource& operator=(AbstractSource const&) = delete;
	AbstractSource& operator=(AbstractSource&&) = default;
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

	void registerInputEvents() override
	{
		registerInputEvent("Queue Update", [this]() {
			queueUpdate();
		});
	}

	void registerOutputEvents() override
	{
	}

	virtual void updateOutputsIfNeeded() const = 0;

};