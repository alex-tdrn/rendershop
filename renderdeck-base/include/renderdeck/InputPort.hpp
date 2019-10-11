#pragma once

#include "renderdeck/AbstractPort.hpp"

template<typename OutputPort>
class InputPort : public virtual AbstractPort
{
protected:
	OutputPort* connection = nullptr;

public:
	InputPort() = default;
	InputPort(InputPort const&) = delete;
	InputPort(InputPort&&) = default;
	InputPort& operator=(InputPort const&) = delete;
	InputPort& operator=(InputPort&&) = default;
	virtual ~InputPort() = default;

public:
	bool isConnected() const final override
	{
		return connection != nullptr;
	}

	bool canConnect(AbstractPort* port) const final override
	{
		if(!dynamic_cast<OutputPort*>(port))
			return false;
		else
			return true;
	}

	void connect(AbstractPort* port) final override
	{
		if(!canConnect(port))
			return;
		connect(dynamic_cast<OutputPort*>(port));
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

	void connect(OutputPort* port)
	{
		if(connection != port)
		{
			disconnect();
			connection = port;
			port->connect(this);
		}
	}

};

