#pragma once

#include "renderdeck/AbstractPipe.hpp"
#include "renderdeck/EventPipe.hpp"

class AbstractDataPort;

class AbstractSink : public virtual AbstractPipe, public virtual EventPipe
{
protected:
	std::vector<AbstractDataPort*> abstractInputDataPorts;

public:
	AbstractSink() = default;
	AbstractSink(AbstractSink const&) = delete;
	AbstractSink(AbstractSink&&) = delete;
	AbstractSink& operator=(AbstractSink const&) = delete;
	AbstractSink& operator=(AbstractSink&&) = delete;
	virtual ~AbstractSink() = default;

	std::vector<AbstractDataPort*> const& getInputDataPorts() const
	{
		return abstractInputDataPorts;
	}

protected:
	virtual void updateAllInputs() const = 0;

public:
	bool allInputsConnected() const
	{
		bool ret = true;
		for(auto inputDataPort : abstractInputDataPorts)
			ret &= inputDataPort->isConnected();
		return ret;
	}

	virtual void trigger() const
	{
		if(!allInputsConnected())
			return;

		updateAllInputs();
		update();
	}

	std::unordered_map<std::string, AbstractInputEventPort> registerInputEvents() const override
	{
		return {};
	}

	std::unordered_map<std::string, OutputEventPort> registerOutputEvents() const override
	{
		return {};
	}

};