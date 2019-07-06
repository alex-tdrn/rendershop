#pragma once
#include "renderdeck/Timestamp.hpp"
#include "renderdeck/OutputPort.hpp"

template<typename T>
class OutputPort;

template<typename T>
class InputPort
{
private:
	Timestamp lastModificationTime;
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

	void disconnect()
	{
		if(connection != nullptr)
		{
			auto oldConnection = connection;
			connection = nullptr;
			oldConnection->disconnect(this);
		}
	}

	T const& getValue() const
	{
		return connection->getValue();
	}

};