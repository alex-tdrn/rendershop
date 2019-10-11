#pragma once

#include "renderdeck/AbstractPort.hpp"

#include <set>

template<typename InputPort>
class OutputPort : public virtual AbstractPort
{
protected:
	std::set<InputPort*> connections;

public:
	OutputPort() = default;
	OutputPort(OutputPort const&) = delete;
	OutputPort(OutputPort&&) = default;
	OutputPort& operator=(OutputPort const& that) = delete;
	OutputPort& operator=(OutputPort&&) = default;
	virtual ~OutputPort() = default;

public:
	bool isConnected() const final override
	{
		return !connections.empty();
	}

	void connect(AbstractPort* port) final override
	{
		if(!canConnect(port))
			return;
		connect(dynamic_cast<InputPort*>(port));
	}

	bool canConnect(AbstractPort* port) const final override
	{
		if(!dynamic_cast<InputPort*>(port))
			return false;
		else
			return true;
	}

	void disconnect() final override
	{
		while(!connections.empty())
		{
			disconnect(*connections.begin());
		}
	}

	void connect(InputPort* port)
	{
		if(connections.find(port) != connections.end())
			return;
		connections.insert(port);
		port->connect(this);
	}

	void disconnect(AbstractPort* port)
	{
		auto castedPort = dynamic_cast<InputPort*>(port);
		if(!castedPort)
			return;
		disconnect(castedPort);
	}

	void disconnect(InputPort* port)
	{
		if(connections.find(port) == connections.end())
			return;
		connections.erase(port);
		port->disconnect();
	}

};
