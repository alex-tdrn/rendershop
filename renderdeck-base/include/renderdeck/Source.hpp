#pragma once

#include "renderdeck/AbstractSource.hpp"
#include "renderdeck/OutputDataPort.hpp"
#include "renderdeck/Utility.hpp"
#include "renderdeck/Timestamp.hpp"

template<typename... O>
struct OutputList
{
	std::tuple<OutputDataPort<O>...> list;
};

template<typename ConcreteSource, typename OutputList>
class Source : public virtual AbstractSource
{
private:
	mutable OutputList outputs;

public:
	Source()
	{
		static_for_index(outputs.list, [&](auto& outputDataPort, int index) {
			AbstractSource::abstractOutputDataPorts.push_back(&outputDataPort);
			outputDataPort.setName(ConcreteSource::OutputPorts::names[index]);
			outputDataPort.setParent(this);
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
	std::string const& getName() const override
	{
		return ConcreteSource::name;
	}

	template<int outputIndex>
	auto& getOutputDataPort() const
	{
		return std::get<outputIndex>(outputs.list);
	}

};