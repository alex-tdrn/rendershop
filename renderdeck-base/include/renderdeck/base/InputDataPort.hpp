#pragma once

#include "renderdeck/base/AbstractDataPort.hpp"
#include "renderdeck/base/InputPort.hpp"
#include "renderdeck/base/OutputDataPort.hpp"

template<typename Data>
class OutputDataPort;

template<typename Data>
class InputDataPort final : public AbstractDataPort, public InputPort<OutputDataPort<Data>>
{
public:
	InputDataPort() = default;
	InputDataPort(InputDataPort const&) = delete;
	InputDataPort(InputDataPort&&) = default;
	InputDataPort& operator=(InputDataPort const&) = delete;
	InputDataPort& operator=(InputDataPort&&) = default;
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

	Data const& get() const
	{
		return this->connection->get();
	}

};