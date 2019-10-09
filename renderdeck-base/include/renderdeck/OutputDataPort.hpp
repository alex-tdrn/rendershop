#pragma once

#include "renderdeck/AbstractDataPort.hpp"
#include "renderdeck/OutputPort.hpp"
#include "renderdeck/InputDataPort.hpp"
#include "renderdeck/AbstractSource.hpp"

template<typename Data>
class InputDataPort;

template<typename Data>
class OutputDataPort final : public DataPort<Data>, public OutputPort<InputDataPort<Data>>
{
private:
	AbstractSource* parent;
	Data resource;

public:
	OutputDataPort() = default;
	OutputDataPort(OutputDataPort const&) = delete;
	OutputDataPort(OutputDataPort&&) = default;
	OutputDataPort& operator=(OutputDataPort const& that) = delete;
	OutputDataPort& operator=(OutputDataPort&&) = default;
	~OutputDataPort() = default;

public:
	void setParent(AbstractSource* parent)
	{
		this->parent = parent;
	}

	Timestamp const& getTimestamp() const final override
	{
		return parent->getTimestamp();
	}

	Data& getMutableData()
	{
		return resource;
	}

	Data const& getData() const final override
	{
		return resource;
	}

	void update() const final override
	{
		parent->updateOutputsIfNeeded();
	}

};