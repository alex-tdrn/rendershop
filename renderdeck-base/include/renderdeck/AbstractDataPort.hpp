#pragma once

#include "renderdeck/AbstractPort.hpp"

class Timestamp;

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

class AbstractDataPort : public virtual AbstractPort
{
public:
	AbstractDataPort() = default;
	AbstractDataPort(AbstractDataPort const&) = delete;
	AbstractDataPort(AbstractDataPort&&) = default;
	AbstractDataPort& operator=(AbstractDataPort const& that) = delete;
	AbstractDataPort& operator=(AbstractDataPort&&) = default;
	virtual ~AbstractDataPort() = default;

public:
	virtual int getDataTypeTag() const = 0;
	virtual Timestamp const& getTimestamp() const = 0;
	virtual void update() const = 0;

};

template <typename T>
class DataPort : public AbstractDataPort
{
public:
	DataPort() = default;
	DataPort(DataPort const&) = delete;
	DataPort(DataPort&&) = default;
	DataPort& operator=(DataPort const& that) = delete;
	DataPort& operator=(DataPort&&) = default;
	virtual ~DataPort() = default;

public:
	virtual T const& getData() const = 0;

	int getDataTypeTag() const final override
	{
		return typeTag<T>();
	}


};