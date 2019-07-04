#pragma once
#include "renderdeck/Timestamp.h"

class Resource
{
protected:
	Timestamp lastModificationTime;

public:
	Resource() = default;
	Resource(Resource const&)
	{
		lastModificationTime.update();
	}
	Resource(Resource&&)
	{
		lastModificationTime.update();
	}
	Resource& operator=(Resource const&)
	{
		lastModificationTime.update();
		return *this;
	}
	Resource& operator=(Resource&&)
	{
		lastModificationTime.update();
		return *this;
	}
	virtual ~Resource() = default;

public:
	Timestamp const& getLastModificationTime() const 
	{
		return lastModificationTime;
	}

};