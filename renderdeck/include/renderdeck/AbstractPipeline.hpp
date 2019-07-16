#pragma once
#include "renderdeck/Timestamp.hpp"

#include <string>
#include <vector>

class AbstractPort
{
protected:
	std::string portName = "Unnamed";

public:
	std::string const& getPortName() const
	{
		return portName;
	}
	virtual int getUnderlyingTypeTag() const = 0;

};

class AbstractOutputPort;

//TODO dynamic connection functions
class AbstractInputPort : public AbstractPort
{
public:
	virtual AbstractOutputPort* getConnectedPort() const = 0;

};

class AbstractOutputPort : public AbstractPort
{
public:
	virtual std::vector<AbstractInputPort*> getConnectedPorts() const = 0;

};

class AbstractPipelineElement
{
protected:
	std::vector<AbstractInputPort*> abstractInputPorts;
	std::vector<AbstractOutputPort*> abstractOutputPorts;

protected:
	virtual void update() const = 0;	

public:
	virtual std::string const& getTypeName() const = 0;
	std::vector<AbstractInputPort*> const& getAbstractInputPorts() const
	{
		return abstractInputPorts;
	}

	std::vector<AbstractOutputPort*> const& getAbstractOutputPorts() const
	{
		return abstractOutputPorts;
	}

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