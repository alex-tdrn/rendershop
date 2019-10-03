#pragma once
#include "renderdeck/AbstractPipe.hpp"
#include "renderdeck/Utility.hpp"
#include "renderdeck/InputResourcePort.hpp"
#include "renderdeck/OutputResourcePort.hpp"

#include <tuple>

template<typename... R>
struct OutputResourceList
{
	std::tuple<OutputResourcePort<R>...> resources;
};

template<typename... R>
struct InputResourceList
{
	std::tuple<InputResourcePort<R>...> resources;
};

template<typename ConcretePipe, typename InputResourceList, typename OutputResourceList>
class Pipe : public AbstractPipe
{
private:
	mutable OutputResourceList outputResources;
	mutable InputResourceList inputResources;

public:
	Pipe()
	{
		static_for_index(outputResources.resources, [&](auto& output, int index) {
			AbstractPipe::abstractOutputResourcePorts.push_back(&output);
			output.setName(ConcretePipe::OutputPorts::names[index]);
			});

		static_for_index(inputResources.resources, [&](auto& input, int index) {
			AbstractPipe::abstractInputResourcePorts.push_back(&input);
			input.setName(ConcretePipe::InputPorts::names[index]);

			});
	}
	Pipe(Pipe const&) = delete;
	Pipe(Pipe&&) = delete;
	Pipe& operator=(Pipe const&) = delete;
	Pipe& operator=(Pipe&&) = delete;
	virtual ~Pipe() = default;

private:
	void trigger() const override
	{
		this->update();
		this->timestamp.update();
	}

	void updateOutputsIfNeeded() const override
	{
		if(!this->allInputsConnected())
			return;

		if(this->isUpdateQueued())
		{
			this->updateAllInputs();
			trigger();
		}
		else
		{
			this->updateAllInputs();

			bool outputsOutdated = false;
			static_for(this->inputResources.resources, [&](auto const& input) {
				if(input.getTimestamp().isNewerThan(this->timestamp))
					outputsOutdated = true;
				});

			if(outputsOutdated)
				trigger();
		}
	}

protected:
	void updateAllInputs() const override final
	{
		static_for(inputResources.resources, [](auto const& input) {
			input.update();
			});
	}

public:
	std::string const& getName() const override final
	{
		return ConcretePipe::name;
	}

	bool allInputsConnected() const final override
	{
		bool ret = true;
		static_for(inputResources.resources, [&](auto const& input) {
			ret &= input.isConnected();
			});
		return ret;
	}

	template<int index>
	auto& getInputResourcePort() const
	{
		return std::get<index>(inputResources.resources);
	}

	template<int index>
	auto& getOutputResourcePort() const
	{
		return std::get<index>(outputResources.resources);
	}
};