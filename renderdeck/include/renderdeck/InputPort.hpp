#pragma once
#include "renderdeck/ResourcePort.hpp"
#include "renderdeck/OutputPort.hpp"

template<typename T>
class OutputPort;

template<typename T>
class InputPort : public ResourcePort<T>
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
	bool connect(OutputPort<T>* port)
	{
		if(connection != port)
		{
			disconnect();
			connection = port;
			if(!port->connect(this))
				connection = nullptr;
			else 
				return true;
		}
		return true;
	}

	bool connect(ResourcePort<T>* port) final override
	{
		auto concretePort = dynamic_cast<OutputPort<T>*>(port);
		if(!concretePort)
			return false;
		else
			return connect(concretePort);
	}

	void disconnect() final override
	{
		if(connection != nullptr)
		{
			auto oldConnection = connection;
			connection = nullptr;
			oldConnection->disconnect(this);
		}
	}

	Timestamp const& getTimestamp() const final override
	{
		return connection->getTimestamp();
	}

	void update() const final override
	{
		if(connection)
			connection->update();
	}

	T const& getResource() const final override
	{
		return connection->getResource();
	}

};