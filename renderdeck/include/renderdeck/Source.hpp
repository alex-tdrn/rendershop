#pragma once
#include "renderdeck/OutputPort.hpp"
#include "renderdeck/Utility.hpp"

#include <tuple>

template<typename... OutputTypes>
class Source : public SourceTypeErased
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
	auto& getOutputPort() const
	{
		return std::get<outputIndex>(outputs);
	}

	virtual void update() const = 0;

};
