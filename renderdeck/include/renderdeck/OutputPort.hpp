#pragma once
#include "renderdeck/AbstractPipeline.hpp"
#include "renderdeck/InputPort.hpp"
#include "renderdeck/TypeTag.hpp"

#include <set>
#include <algorithm>

template<typename T>
class InputPort;

template<typename T>
class OutputPort : public AbstractOutputPort
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
	int getUnderlyingTypeTag() const override
	{
		return typeTag<T>();
	}

	void setName(std::string name)
	{
		this->portName = name;
	}

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


	T& getMutableValue()
	{
		return value;
	}

	void update() const
	{
		parent->updateOutputsIfNeeded();
	}

	T const& getCachedValue() const
	{
		return value;
	}

	Timestamp const& getCachedTimestamp() const
	{
		return parent->getTimestamp();
	}

};