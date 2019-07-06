#pragma once
#include "renderdeck/AbstractPipeline.hpp"
#include "renderdeck/OutputPort.hpp"
#include "renderdeck/Utility.hpp"

#include <tuple>

template<typename... OutputTypes>
class Source : public AbstractSource
{
private:
	mutable std::tuple<OutputPort<OutputTypes>...> outputs;
	
public:
	Source()
	{
		static_for(outputs, [&](auto& output) {
			output.setParent(this);
		});
	}
	Source(Source const&) = delete;
	Source(Source&&) = delete;
	Source& operator=(Source const&) = delete;
	Source& operator=(Source&&) = delete;
	virtual ~Source() = default;

private:
	void updateOutputsIfNeeded() const
	{
		if(isUpdateQueued())
			update();
		timestamp.update();
	}

public:
	template<int outputIndex>
	auto& getOutputPort() const
	{
		return std::get<outputIndex>(outputs);
	}

};
