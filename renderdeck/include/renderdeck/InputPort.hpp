#pragma once
#include "renderdeck/AbstractPipeline.hpp"
#include "renderdeck/OutputPort.hpp"
#include "renderdeck/TypeTag.hpp"

template<typename T>
class OutputPort;

template<typename T>
class InputPort : public AbstractInputPort
{
private:
	OutputPort<T>* connection = nullptr;

public:
	InputPort() = default;
	InputPort(InputPort const&) = delete;
	InputPort(InputPort&&) = delete;
	InputPort& operator=(InputPort const&) = delete;
	InputPort& operator=(InputPort&&) = delete;
	~InputPort() = default;

public:
	int getUnderlyingTypeTag() const override
	{
		return typeTag<T>();
	}

	void setName(std::string name)
	{
		this->portName = name;
	}

	void connect(OutputPort<T>* port)
	{
		if(connection != port)
		{
			disconnect();
			connection = port;
			port->connect(this);
		}
	}

	void disconnect()
	{
		if(connection != nullptr)
		{
			auto oldConnection = connection;
			connection = nullptr;
			oldConnection->disconnect(this);
		}
	}

	void update() const
	{
		connection->update();
	}

	T const& getCachedValue() const
	{
		return connection->getCachedValue();
	}

	Timestamp const& getCachedTimestamp() const
	{
		return connection->getCachedTimestamp();
	}

	AbstractOutputPort* getConnectedPort() const override
	{
		return connection;
	}

};