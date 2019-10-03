#pragma once
#include "renderdeck/AbstractPort.hpp"
#include "renderdeck/Timestamp.hpp"

namespace detail
{
	inline int tag = 0;
}

template <typename T>
int typeTag()
{
	static int tag = detail::tag++;
	return tag;
}

class AbstractResourcePort : public virtual AbstractPort
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

};