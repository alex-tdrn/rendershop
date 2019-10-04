#pragma once
#include "renderdeck/Timestamp.hpp"
#include "renderdeck/InputDataPort.hpp"
#include "renderdeck/OutputDataPort.hpp"

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

public:
	AbstractPipe() = default;
	AbstractPipe(AbstractPipe const&) = delete;
	AbstractPipe(AbstractPipe&&) = delete;
	AbstractPipe& operator=(AbstractPipe const&) = delete;
	AbstractPipe& operator=(AbstractPipe&&) = delete;
	virtual ~AbstractPipe() = default;

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
};
