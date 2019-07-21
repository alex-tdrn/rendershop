#pragma once
#include "renderdeck/AbstractPort.hpp"
#include "renderdeck/TypeTag.hpp"
#include "renderdeck/Timestamp.hpp"

class AbstractResourcePort : public AbstractPort
{
public:
	virtual int getResourceTypeTag() const = 0;
	virtual Timestamp const& getTimestamp() const = 0;
	virtual void update() const = 0;

};

template <typename T>
class ResourcePort : public AbstractResourcePort
{
public:
	int getResourceTypeTag() const final override
	{
		return typeTag<T>();
	}

	virtual T const& getResource() const = 0;
	virtual bool connect(ResourcePort<T>* port) = 0;
	bool connect(AbstractPort* port) final override
	{
		auto concretePort = dynamic_cast<ResourcePort<T>*>(port);
		if(!concretePort)
			return false;
		else 
			return connect(concretePort);
	}

};