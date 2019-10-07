#pragma once

#include "renderdeck/AbstractDataPort.hpp"
#include "renderdeck/InputPort.hpp"
#include "renderdeck/OutputDataPort.hpp"

template<typename Data>
class OutputDataPort;

template<typename Data>
class InputDataPort : public DataPort<Data>, public InputPort<OutputDataPort<Data>>
{
public:
	InputDataPort() = default;
	InputDataPort(InputDataPort const&) = delete;
	InputDataPort(InputDataPort&&) = delete;
	InputDataPort& operator=(InputDataPort const&) = delete;
	InputDataPort& operator=(InputDataPort&&) = delete;
	~InputDataPort() = default;

public:
	Timestamp const& getTimestamp() const final override
	{
		return this->connection->getTimestamp();
	}

	void update() const final override
	{
		if(this->connection)
			this->connection->update();
	}

	Data const& getData() const final override
	{
		return this->connection->getData();
	}

};