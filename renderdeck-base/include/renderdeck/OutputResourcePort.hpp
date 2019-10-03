#pragma once
#include "renderdeck/AbstractResourcePort.hpp"
#include "renderdeck/OutputPort.hpp"
#include "renderdeck/InputResourcePort.hpp"

template<typename Resource>
class InputResourcePort;

template<typename Resource>
class OutputResourcePort : public ResourcePort<Resource>, public OutputPort<InputResourcePort<Resource>>
{
private:
	Resource resource;

public:
	OutputResourcePort() = default;
	OutputResourcePort(OutputResourcePort const&) = delete;
	OutputResourcePort(OutputResourcePort&&) = delete;
	OutputResourcePort& operator=(OutputResourcePort const& that) = delete;
	OutputResourcePort& operator=(OutputResourcePort&&) = delete;
	~OutputResourcePort() = default;

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