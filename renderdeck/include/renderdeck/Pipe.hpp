#pragma once
#include "renderdeck/Source.hpp"
#include "renderdeck/Sink.hpp"
#include "renderdeck/Utility.hpp"

template<typename Si, typename So>
class Pipe : public Si, public So
{
public:
	Pipe() = default;
	Pipe(Pipe const&) = delete;
	Pipe(Pipe&&) = delete;
	Pipe& operator=(Pipe const&) = delete;
	Pipe& operator=(Pipe&&) = delete;
	virtual ~Pipe() = default;

private:
	void trigger() const override
	{
		this->update();
		this->timestamp.update();
	}

	void updateOutputsIfNeeded() const override
	{
		if(this->isUpdateQueued())
		{
			trigger();
		}
		else
		{
			bool outputsOutdated = false;
			static_for(this->inputs, [&](auto const& input) {
				if(input.getTimestamp().isNewerThan(this->timestamp))
					outputsOutdated = true;
			});

			if(outputsOutdated)
				trigger();
		}
	}

};