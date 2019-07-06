#pragma once
#include "renderdeck/Timestamp.hpp"
#include "renderdeck/InputPort.hpp"

#include <set>
#include <algorithm>

class SourceTypeErased
{
public:
	virtual void update() const = 0;
};

template<typename T>
class InputPort;

template<typename T>
class OutputPort
{
public:
	class ModificationGuard
	{
	private:
		OutputPort<T>& port;

	public:
		T& value;

	public:
		ModificationGuard() = delete;
		ModificationGuard(OutputPort<T>& port, T& value)
			: port(port), value(value)
		{

		}
		~ModificationGuard()
		{
			port.lastModificationTime.update();
		}
	};

private:
	SourceTypeErased* parent;
	T value;
	Timestamp lastModificationTime;
	std::set<InputPort<T>*> connections;

public:
	OutputPort() = default;
	OutputPort(OutputPort const&) = delete;
	OutputPort(OutputPort&& that)
	{
		this->value = std::move(that.value);
	}
	OutputPort& operator=(OutputPort const& that) = delete;
	OutputPort& operator=(OutputPort&& that)
	{
		this->value = std::move(that.value);
		lastModificationTime.update();
		return *this;
	}
	~OutputPort() = default;

public:
	void setParent(SourceTypeErased* parent)
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

	}

	OutputPort<T>::ModificationGuard getModificationGuard()
	{
		return { *this, value };
	}

	T const& getValue() const
	{
		parent->update();
		return value;
	}

	bool isInitialized() const
	{
		return !lastModificationTime.isReset();
	}

};