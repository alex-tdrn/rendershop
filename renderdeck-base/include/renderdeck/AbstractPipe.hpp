#pragma once
#include "renderdeck/Timestamp.hpp"
#include "renderdeck/InputResourcePort.hpp"
#include "renderdeck/OutputResourcePort.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cassert>

class AbstractPipe
{
private:
	static inline std::unordered_map<std::string, std::unique_ptr<AbstractPipe>(*)()> allPipes;

protected:
	mutable Timestamp timestamp;
	std::vector<AbstractResourcePort*> inputResourcePorts;
	std::vector<AbstractResourcePort*> outputResourcePorts;
	std::vector<AbstractPort*> inputEventPorts;
	std::vector<AbstractPort*> outputEventPorts;

protected:
	virtual void update() const = 0;
	template <typename ConcretePipe>
	static std::string registerPipe(std::string name)
	{
		allPipes[name] = []() {
			std::unique_ptr<AbstractPipe> ptr = std::make_unique<ConcretePipe>();
			return ptr;
		};
		return name;
	}

public:
	static std::unordered_map<std::string, std::unique_ptr<AbstractPipe>(*)()> const& getAllPipes()
	{
		return allPipes;
	}

	static std::unique_ptr<AbstractPipe> createPipe(std::string const name)
	{
		assert(allPipes.find(name) != allPipes.end());

		return allPipes[name]();
	}

	Timestamp const& getTimestamp() const
	{
		return timestamp;
	}

	virtual std::string const& getName() const = 0;

	std::vector<AbstractResourcePort*> const& getInputResourcePorts() const
	{
		return inputResourcePorts;
	}

	std::vector<AbstractResourcePort*> const& getOutputResourcePorts() const
	{
		return outputResourcePorts;
	}

	std::vector<AbstractPort*> const& getInputEventPorts() const
	{
		return inputEventPorts;
	}

	std::vector<AbstractPort*> const& getOutputEventPorts() const
	{
		return outputEventPorts;
	}


protected:
	virtual void updateAllInputs() const = 0;

public:
	virtual bool allInputsConnected() const = 0;

	virtual void trigger() const
	{
		if(!allInputsConnected())
			return;

		updateAllInputs();
		update();
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
