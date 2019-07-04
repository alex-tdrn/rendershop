#pragma once
#include "renderdeck/Resource.h"

#include <vector>
#include <memory>

class Source : public Resource
{
protected:
	std::vector<std::unique_ptr<Resource>> outputs;
	
public:
	Source() = default;
	Source(Source const&) = delete;
	Source(Source&&) = delete;
	Source& operator=(Source const&) = delete;
	Source& operator=(Source&&) = delete;
	virtual ~Source() = default;

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
