#pragma once
#include "renderdeck/Source.hpp"
#include "renderdeck/Sink.hpp"
#include "renderdeck/Utility.hpp"

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
	std::string const& getTypeName() const override
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
				if(input.getCachedTimestamp().isNewerThan(this->timestamp))
					outputsOutdated = true;
			});

			if(outputsOutdated)
				trigger();
		}
	}

};