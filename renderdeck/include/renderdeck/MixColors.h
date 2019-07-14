#pragma once
#include "renderdeck/Pipe.hpp"

#include <glm/glm.hpp>
#include <array>

class MixColors : public Pipe<MixColors, InputList<float, glm::vec3, glm::vec3>, OutputList<glm::vec3>>
{
public:
	static inline std::string const name = "Mix Colors";
	
	struct InputPorts
	{
		static inline std::array names = {
			"Factor",
			"Color A",
			"Color B"
		};
		enum {
			Factor,
			ColorA,
			ColorB
		};
	};

	struct OutputPorts
	{
		static inline std::array names = {
			"Mixed Color"
		};
		enum {
			MixedColor
		};

	};

public:
	void update() const override
	{
		auto& factor = getInputPort<InputPorts::Factor>().getCachedValue();
		auto& colorA= getInputPort<InputPorts::ColorA>().getCachedValue();
		auto& colorB = getInputPort<InputPorts::ColorB>().getCachedValue();
		auto& mixedColor = getOutputPort<OutputPorts::MixedColor>().getMutableValue();

		mixedColor = factor * colorA + (1 - factor) * colorB;
	}

};

