#pragma once

#include "renderdeck/Source.hpp"
#include "renderdeck/Sink.hpp"

template<typename ConcretePipe, typename InputList, typename OutputList>
class Pipe : virtual public Sink<ConcretePipe, InputList>, virtual public Source<ConcretePipe, OutputList>
{
public:
	Pipe() = default;
	Pipe(Pipe const&) = delete;
	Pipe(Pipe&&) = delete;
	Pipe& operator=(Pipe const&) = delete;
	Pipe& operator=(Pipe&&) = delete;
	virtual ~Pipe() = default;

private:
	std::string const& getName() const override final
	{
		return ConcretePipe::name;
	}

	void trigger() const override
	{
		this->update();
		this->timestamp.update();
	}

	void updateOutputsIfNeeded() const override
	{
		if(!this->allInputsConnected())
			return;

		if(this->isUpdateQueued())
		{
			this->updateAllInputs();
			trigger();
		}
		else
		{
			this->updateAllInputs();

			bool outputsOutdated = false;
			static_for(this->inputs.list, [&](auto const& input) {
				if(input.getTimestamp().isNewerThan(this->timestamp))
					outputsOutdated = true;
				});

			if(outputsOutdated)
				trigger();
		}
	}

	std::unordered_map<std::string, std::unique_ptr<InputEventPort>> registerInputEvents() override
	{
		auto inputEvents = AbstractSink::registerInputEvents();
		inputEvents.merge(AbstractSource::registerInputEvents());
		return inputEvents;
	}

	std::unordered_map<std::string, OutputEventPort> registerOutputEvents() override
	{
		auto outputEvents = AbstractSink::registerOutputEvents();
		outputEvents.merge(AbstractSource::registerOutputEvents());
		return outputEvents;
	}

};