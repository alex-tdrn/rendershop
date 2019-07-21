#pragma once
#include <string>

class AbstractPort
{
private:
	std::string name = "Unnamed";

public:
	std::string const& getName() const
	{
		return name;
	}

	void setName(std::string const& name)
	{
		this->name = name;
	}
	
	virtual bool connect(AbstractPort* port) = 0;
	virtual void disconnect() = 0;

};
