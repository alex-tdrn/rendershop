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
	void connect(OutputPort<T>* port)
	{
		if(connection != port)
		{
			disconnect();
			connection = port;
			port->connect(this);
		}
	}

	void connect(AbstractPort* port) final override
	{
		if(!canConnect(port))
			return;
		connect(static_cast<OutputPort<T>*>(port));
	}

	bool canConnect(AbstractPort* port) final override
	{
		if(!dynamic_cast<OutputPort<T>*>(port))
			return false;
		else
			return true;
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