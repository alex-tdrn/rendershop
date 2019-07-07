#pragma once
#include "renderdeck/AbstractPipeline.hpp"
#include "renderdeck/InputPort.hpp"
#include "renderdeck/Utility.hpp"

#include <tuple>

template<typename... InputTypes>
class Sink : public virtual AbstractSink
{
protected:
	mutable std::tuple<InputPort<InputTypes>...> inputs;

public:
	Sink() = default;
	Sink(Sink const&) = delete;
	Sink(Sink&&) = delete;
	Sink& operator=(Sink const&) = delete;
	Sink& operator=(Sink&&) = delete;
	virtual ~Sink() = default;

protected:
	void updateAllInputs() const override final
	{
		static_for(inputs, [](auto const& input) {
			input.update();
		});
	}

public:
	template<int inputIndex>
	auto& getInputPort() const
	{
		return std::get<inputIndex>(inputs);
	}

};
