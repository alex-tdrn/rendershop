#pragma once
#include "renderdeck/ResourcePort.hpp"
#include "renderdeck/InputPort.hpp"

#include <set>
#include <algorithm>

template<typename T>
class InputPort;

template<typename T>
class OutputPort : public ResourcePort<T>
{
private:
	std::set<InputPort<T>*> connections;
	AbstractSource* parent;
	T resource;

public:
	OutputPort() = default;
	OutputPort(OutputPort const&) = delete;
	OutputPort(OutputPort&&) = delete;
	OutputPort& operator=(OutputPort const& that) = delete;
	OutputPort& operator=(OutputPort&&) = delete;
	~OutputPort() = default;

public:
	void connect(InputPort<T>* port)
	{
		if(connections.find(port) != connections.end())
			return;
		connections.insert(port);
		port->connect(this);
	}

	void connect(AbstractPort* port) final override
	{
		if(!canConnect(port))
			return;
		connect(static_cast<InputPort<T>*>(port));
	}

	bool canConnect(AbstractPort* port) final override
	{
		if(!dynamic_cast<InputPort<T>*>(port))
			return false;
		else
			return true;
	}

	void disconnect(InputPort<T>* port)
	{
		if(connections.find(port) == connections.end())
			return;
		connections.erase(port);
		port->disconnect();
	}

	void disconnect() final override
	{
		while(!connections.empty())
		{
			disconnect(*connections.begin());
		}
	}

	Timestamp const& getTimestamp() const final override
	{
		return parent->getTimestamp();
	}

	void setParent(AbstractSource* parent)
	{
		this->parent = parent;
	}

	T& getMutableResource()
	{
		return resource;
	}

	T const& getResource() const final override
	{
		return resource;
	}

	void update() const final override
	{
		parent->updateOutputsIfNeeded();
	}

};