#pragma once

#include "renderdeck/AbstractPipe.hpp"
#include "renderdeck/EventPipe.hpp"
#include "renderdeck/AbstractDataPort.hpp"

class AbstractSink : public virtual AbstractPipe, public virtual EventPipe
{
protected:
	std::vector<AbstractDataPort*> abstractInputDataPorts;

public:
	AbstractSink() = default;
	AbstractSink(AbstractSink const&) = delete;
	AbstractSink(AbstractSink&&) = default;
	AbstractSink& operator=(AbstractSink const&) = delete;
	AbstractSink& operator=(AbstractSink&&) = default;
	virtual ~AbstractSink() = default;


protected:
	virtual void updateAllInputs() const = 0;

public:
	void registerInputEvents() override
	{
		registerInputEvent("Trigger", [this]() {
			trigger();
		});
	}

	void registerOutputEvents() override
	{
	}

	std::vector<AbstractDataPort*> const& getInputDataPorts() const
	{
		return abstractInputDataPorts;
	}

	bool allInputsConnected() const
	{
		bool ret = true;
		for(auto inputDataPort : abstractInputDataPorts)
			ret &= inputDataPort->isConnected();
		return ret;
	}

	virtual void trigger()
	{
		if(!allInputsConnected())
			return;

		updateAllInputs();
		update();
	}

};