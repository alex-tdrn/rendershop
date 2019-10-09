#pragma once

#include <string>

class AbstractPort
{
private:
	std::string name = "Unnamed";

public:
	AbstractPort() = default;
	AbstractPort(AbstractPort const&) = delete;
	AbstractPort(AbstractPort&&) = default;
	AbstractPort& operator=(AbstractPort const& that) = delete;
	AbstractPort& operator=(AbstractPort&&) = default;
	virtual ~AbstractPort() = default;

public:
	std::string const& getName() const
	{
		return name;
	}

	void setName(std::string const& name)
	{
		this->name = name;
	}
	
	virtual bool canConnect(AbstractPort* port) const = 0;
	virtual bool isConnected() const = 0;
	virtual void connect(AbstractPort* port) = 0;
	virtual void disconnect() = 0;

};
