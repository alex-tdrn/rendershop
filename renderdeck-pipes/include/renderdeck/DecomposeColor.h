#pragma once
#include "renderdeck/Pipe.hpp"

#include <glm/glm.hpp>
#include <array>

class DecomposeColor : public Pipe<DecomposeColor, InputList<glm::vec3>, OutputList<float, float, float>>
{
public:
	static inline std::string const name = registerPipelineElement<DecomposeColor>("Decompose Colors");

	struct InputPorts
	{
		static inline std::array names = {
			"Color"
		};
		enum {
			Color
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
		auto& color = getInputPort<InputPorts::Color>().getResource();
		auto& r = getOutputPort<OutputPorts::R>().getMutableResource();
		auto& g = getOutputPort<OutputPorts::G>().getMutableResource();
		auto& b = getOutputPort<OutputPorts::B>().getMutableResource();

		r = color.r;
		g = color.g;
		b = color.b;
	}

};

