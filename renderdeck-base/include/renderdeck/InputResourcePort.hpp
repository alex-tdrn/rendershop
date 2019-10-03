#pragma once
#include "renderdeck/AbstractResourcePort.hpp"
#include "renderdeck/InputPort.hpp"
#include "renderdeck/OutputResourcePort.hpp"

template<typename Resource>
class OutputResourcePort;

template<typename Resource>
class InputResourcePort : public ResourcePort<Resource>, public InputPort<OutputResourcePort<Resource>>
{
public:
	InputResourcePort() = default;
	InputResourcePort(InputResourcePort const&) = delete;
	InputResourcePort(InputResourcePort&&) = delete;
	InputResourcePort& operator=(InputResourcePort const&) = delete;
	InputResourcePort& operator=(InputResourcePort&&) = delete;
	~InputResourcePort() = default;

public:
	Timestamp const& getTimestamp() const final override
	{
		return connection->getTimestamp();
	}

	void update() const final override
	{
		if(connection)
			connection->update();
	}

	Resource const& getResource() const final override
	{
		return connection->getResource();
	}

};