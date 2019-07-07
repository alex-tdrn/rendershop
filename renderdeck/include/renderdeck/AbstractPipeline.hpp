#pragma once
#include "renderdeck/Timestamp.hpp"

class AbstractPipelineElement
{
protected:
	virtual void update() const = 0;	

};

class AbstractSource : public virtual AbstractPipelineElement
{
protected:
	mutable Timestamp timestamp;

public:
	AbstractSource() = default;
	virtual ~AbstractSource() = default;

protected:
	bool isUpdateQueued() const
	{
		return timestamp.isReset();
	}

public:
	Timestamp const& getTimestamp() const
	{
		return timestamp;
	}

	void queueUpdate()
	{
		timestamp.reset();
	}

	virtual void updateOutputsIfNeeded() const = 0;

};

class AbstractSink : public virtual AbstractPipelineElement
{
protected:
	virtual void updateAllInputs() const = 0;

public:
	virtual void trigger() const
	{
		updateAllInputs();
		update();
	}
};