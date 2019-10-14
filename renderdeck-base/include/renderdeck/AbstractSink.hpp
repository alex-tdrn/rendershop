#pragma once

#include "renderdeck/AbstractPipe.hpp"
#include "renderdeck/EventPipe.hpp"
#include "renderdeck/AbstractDataPort.hpp"

class AbstractSink : public virtual AbstractPipe
{
public:
	struct InputEvents
	{
		enum
		{
			Run = AbstractPipe::InputEvents::SinkEvents
		};
	};

	struct OutputEvents
	{
		enum
		{
		};
	};

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
		AbstractPipe::registerInputEvents();
		registerInputEvent(InputEvents::Run, "Run", [this]() {
			run();
		});
	}

	void registerOutputEvents() override
	{
		AbstractPipe::registerOutputEvents();
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

	virtual void run()
	{
		if(!allInputsConnected())
			return;

		updateAllInputs();
		trigger(AbstractPipe::OutputEvents::Updated);
		update();
	}

};