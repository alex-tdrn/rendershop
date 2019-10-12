#pragma once

#include "renderdeck/Source.hpp"
#include "renderdeck/Sink.hpp"

template<typename ConcretePipe, typename InputList, typename OutputList>
class Pipe : virtual public Sink<ConcretePipe, InputList>, virtual public Source<ConcretePipe, OutputList>
{
public:
	Pipe() = default;
	Pipe(Pipe const&) = delete;
	Pipe(Pipe&&) = default;
	Pipe& operator=(Pipe const&) = delete;
	Pipe& operator=(Pipe&&) = default;
	virtual ~Pipe() = default;

private:
	std::string const& getName() const override final
	{
		return ConcretePipe::name;
	}

	void run() override
	{
		this->update();
		this->timestamp.update();
	}

	void updateOutputsIfNeeded() override
	{
		if(!this->allInputsConnected())
			return;

		if(this->isUpdateQueued())
		{
			this->updateAllInputs();
			run();
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
				run();
		}
	}

	void registerInputEvents() override
	{
		AbstractSink::registerInputEvents();
		AbstractSource::registerInputEvents();
	}

	void registerOutputEvents() override
	{
		AbstractSink::registerOutputEvents();
		AbstractSource::registerOutputEvents();
	}

};