#pragma once
#include "renderdeck/AbstractPipeline.hpp"
#include "renderdeck/InputPort.hpp"

#include <set>
#include <algorithm>

template<typename T>
class InputPort;

template<typename T>
class OutputPort
{
private:
	AbstractSource* parent;
	T value;
	std::set<InputPort<T>*> connections;

public:
	OutputPort() = default;
	OutputPort(OutputPort const&) = delete;
	OutputPort(OutputPort&&) = delete;
	OutputPort& operator=(OutputPort const& that) = delete;
	OutputPort& operator=(OutputPort&&) = delete;
	~OutputPort() = default;

public:
	void setParent(AbstractSource* parent)
	{
		this->parent = parent;
	}

	void connect(InputPort<T>* port)
	{
		if(connections.find(port) == connections.end())
			return;
		connections.insert(port);
		port->connect(this);
	}

	void disconnect(InputPort<T>* port)
	{
		if(connections.find(port) == connections.end())
			return;
		connections.erase(port);
		port->disconnect();
	}

	void disconnectAll()
	{
		while(!connections.empty())
		{
			disconnect(*connections.begin());
		}
	}

	Timestamp const* getLastModificationTime() const
	{
		return parent->getLastModificationTime();
	}

	T& getMutableValue()
	{
		return value;
	}

	T const& getValue() const
	{
		parent->updateOutputsIfNeeded();
		return value;
	}

	Timestamp const& getTimestamp() const
	{
		parent->updateOutputsIfNeeded();
		return parent->getTimestamp();
	}

};