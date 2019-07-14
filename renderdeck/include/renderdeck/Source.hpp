#pragma once
#include "renderdeck/AbstractPipeline.hpp"
#include "renderdeck/OutputPort.hpp"
#include "renderdeck/Utility.hpp"

#include <tuple>

template<typename... O>
struct OutputList
{
	std::tuple<OutputPort<O>...> list;
};

template<typename ConcreteSource, typename OutputList>
class Source : public virtual AbstractSource
{
private:
	mutable OutputList outputs;
	
public:
	Source()
	{
		static_for_index(outputs.list, [&](auto& output, int index) {
			output.setParent(this);
			output.setName(ConcreteSource::OutputPorts::names[index]);
			abstractOutputPorts.push_back(&output);
		});
	}
	Source(Source const&) = delete;
	Source(Source&&) = delete;
	Source& operator=(Source const&) = delete;
	Source& operator=(Source&&) = delete;
	virtual ~Source() = default;

protected:
	void updateOutputsIfNeeded() const override
	{
		if(isUpdateQueued())
		{
			update();
			timestamp.update();
		}
	}

public:
	std::string const& getTypeName() const override final
	{
		return ConcreteSource::name;
	}

	template<int outputIndex>
	auto& getOutputPort() const
	{
		return std::get<outputIndex>(outputs.list);
	}

};
