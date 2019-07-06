#pragma once
#include "Connection.h"

#include <vector>
#include <memory>

class Source
{
private:
	std::vector<std::vector<std::shared_ptr<Connection>>> connections;

protected:
	std::vector<Resource> outputs;
	
public:
	Source() = default;
	Source(Source const&) = delete;
	Source(Source&&) = delete;
	Source& operator=(Source const&) = delete;
	Source& operator=(Source&&) = delete;
	virtual ~Source() = default;

public:
	void setNumberOfOutputPorts(int n)
	{
		
	}

public:
	Resource const* get(int outputIndex) const
	{
		Resource const* output = outputs[outputIndex].get();
		if(output->getLastModificationTime().isReset())
			update();
		return output;
	}
	virtual void update() const = 0;

};
