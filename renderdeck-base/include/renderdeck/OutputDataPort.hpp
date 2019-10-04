#pragma once
#include "renderdeck/AbstractDataPort.hpp"
#include "renderdeck/OutputPort.hpp"
#include "renderdeck/InputDataPort.hpp"

template<typename Data>
class InputDataPort;

template<typename Data>
class OutputDataPort : public DataPort<Data>, public OutputPort<InputDataPort<Data>>
{
private:
	Data resource;

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

	Data& getMutableData()
	{
		return resource;
	}

	Data const& getData() const final override
	{
		return resource;
	}

	void update() const final override
	{
		//TODO
		//parent->updateOutputsIfNeeded();
	}

};