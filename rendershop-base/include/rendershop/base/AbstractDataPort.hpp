#pragma once

#include "rendershop/base/AbstractPort.hpp"

class Timestamp;

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
	virtual Timestamp const& getTimestamp() const = 0;
	virtual void update() const = 0;

};
