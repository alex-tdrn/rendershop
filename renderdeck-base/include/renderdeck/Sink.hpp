#pragma once
#include "renderdeck/AbstractPipeline.hpp"
#include "renderdeck/InputPort.hpp"
#include "renderdeck/Utility.hpp"

#include <string>
#include <tuple>

template<typename... I>
struct InputList
{
	std::tuple<InputPort<I>...> list;
};

template<typename ConcreteSink, typename InputList>
class Sink : public virtual AbstractSink
{
protected:
	mutable InputList inputs;

public:
	Sink()
	{
		static_for_index(inputs.list, [&](auto& input, int index) {
			abstractInputPorts.push_back(&input);
			input.setName(ConcreteSink::InputPorts::names[index]);

		});
	}
	Sink(Sink const&) = delete;
	Sink(Sink&&) = delete;
	Sink& operator=(Sink const&) = delete;
	Sink& operator=(Sink&&) = delete;
	virtual ~Sink() = default;

protected:
	void updateAllInputs() const override final
	{
		static_for(inputs.list, [](auto const& input) {
			input.update();
		});
	}

public:
	std::string const& getTypeName() const override
	{
		return ConcreteSink::name;
	}

	bool allInputsConnected() const final override
	{
		bool ret = true;
		static_for(inputs.list, [&](auto const& input) {
			ret &= input.isConnected();
		});
		return ret;
	}

	template<int inputIndex>
	auto& getInputPort() const
	{
		return std::get<inputIndex>(inputs.list);
	}

};
