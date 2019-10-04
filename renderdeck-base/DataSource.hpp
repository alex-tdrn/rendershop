#pragma once
#include "renderdeck/AbstractDataSource.hpp"

class DataSource : public AbstractDataSource
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

	virtual void updateOutputsIfNeeded() const = 0;

};