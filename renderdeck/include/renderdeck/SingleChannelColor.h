#pragma once
#include "renderdeck/Pipe.hpp"

#include <glm/glm.hpp>
#include <array>

class ValueToColor : public Pipe<ValueToColor, InputList<glm::vec3>, OutputList<float, float, float>>
{
public:
	static inline std::string const name = "Value To Color";

	struct InputPorts
	{
		static inline std::array names = {
			"Value"
		};
		enum {
			Value
		};

	};
	struct OutputPorts
	{
		static inline std::array names = {
			"R",
			"G",
			"B"
		};
		enum {
			R,
			G,
			B
		};
	};


public:
	void update() const override
	{
		auto& color = getInputPort<InputPorts::Color>().getCachedValue();
		auto& r = getOutputPort<OutputPorts::R>().getMutableValue();
		auto& g = getOutputPort<OutputPorts::G>().getMutableValue();
		auto& b = getOutputPort<OutputPorts::B>().getMutableValue();

		r = color.r;
		g = color.g;
		b = color.b;
	}

};

