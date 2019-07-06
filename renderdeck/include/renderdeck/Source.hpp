#pragma once
#include "renderdeck/OutputPort.hpp"
#include "renderdeck/Utility.hpp"

#include <tuple>

template<typename... OutputTypes>
class Source
{
private:
	mutable std::tuple<OutputPort<OutputTypes>...> outputs;
	
public:
	Source() = default;
	Source(Source const&) = delete;
	Source(Source&&) = delete;
	Source& operator=(Source const&) = delete;
	Source& operator=(Source&&) = delete;
	virtual ~Source() = default;

private:
	void checkOutputs() const
	{
		bool outputsOutdated = false;
		static_for(outputs, [&outputsOutdated](auto const& output) {
			if(!output.isInitialized())
				outputsOutdated = true;
		});
		if(outputsOutdated)
			update();
	}

protected:
	template<int outputIndex>
	auto getModificationGuard() const
	{
		return std::get<outputIndex>(outputs).getModificationGuard();
	}

public:
	template<int outputIndex>
	auto const& getValue() const
	{
		checkOutputs();
		return std::get<outputIndex>(outputs).getValue();
	}

	virtual void update() const = 0;

};
