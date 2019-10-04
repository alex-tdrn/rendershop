#pragma once
#include "renderdeck/AbstractDataPort.hpp"
#include "renderdeck/OutputPort.hpp"
#include "renderdeck/InputDataPort.hpp"

template<typename Resource>
class InputDataPort;

template<typename Resource>
class OutputDataPort : public DataPort<Resource>, public OutputPort<InputDataPort<Resource>>
{
private:
	Resource resource;

public:
	OutputDataPort() = default;
	OutputDataPort(OutputDataPort const&) = delete;
	OutputDataPort(OutputDataPort&&) = delete;
	OutputDataPort& operator=(OutputDataPort const& that) = delete;
	OutputDataPort& operator=(OutputDataPort&&) = delete;
	~OutputDataPort() = default;

public:
	Timestamp const& getTimestamp() const final override
	{
		//TODO
		return {};//parent->getTimestamp();
	}

	Resource& getMutableResource()
	{
		return resource;
	}

	Resource const& getResource() const final override
	{
		return resource;
	}

	void update() const final override
	{
		//TODO
		//parent->updateOutputsIfNeeded();
	}

};