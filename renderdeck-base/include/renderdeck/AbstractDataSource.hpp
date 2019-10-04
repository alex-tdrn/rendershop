#pragma once
#include "renderdeck/AbstractPipe.hpp"

class AbstractDataSource : public virtual AbstractPipe
{
protected:
	std::vector<AbstractDataPort*> abstractOutputDataPorts;

public:
	AbstractDataSource() = default;
	AbstractDataSource(AbstractDataSource const&) = delete;
	AbstractDataSource(AbstractDataSource&&) = delete;
	AbstractDataSource& operator=(AbstractDataSource const&) = delete;
	AbstractDataSource& operator=(AbstractDataSource&&) = delete;
	virtual ~AbstractDataSource() = default;

	std::vector<AbstractDataPort*> const& getOutputDataPorts() const
	{
		return abstractOutputDataPorts;
	}

protected:
	bool isUpdateQueued() const
	{
		return timestamp.isReset();
	}

public:
	void queueUpdate()
	{
		timestamp.reset();
	}

};