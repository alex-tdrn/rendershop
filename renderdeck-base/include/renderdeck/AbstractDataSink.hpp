#pragma once
#include "renderdeck/AbstractPipe.hpp"

class AbstractDataSink : public virtual AbstractPipe
{
protected:
	std::vector<AbstractDataPort*> abstractInputDataPorts;

public:
	AbstractDataSink() = default;
	AbstractDataSink(AbstractDataSink const&) = delete;
	AbstractDataSink(AbstractDataSink&&) = delete;
	AbstractDataSink& operator=(AbstractDataSink const&) = delete;
	AbstractDataSink& operator=(AbstractDataSink&&) = delete;
	virtual ~AbstractDataSink() = default;

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

};