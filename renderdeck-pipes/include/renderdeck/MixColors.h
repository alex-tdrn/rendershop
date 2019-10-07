#pragma once
#include "renderdeck/Pipe.hpp"

#include <glm/glm.hpp>
#include <array>

class MixColors : public Pipe<MixColors, InputList<float, glm::vec3, glm::vec3>, OutputList<glm::vec3>>
{
public:
	static inline std::string const name = registerPipe<MixColors>("Mix Colors");
	
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
		auto& factor = getInputDataPort<InputPorts::Factor>().getData();
		auto& colorA= getInputDataPort<InputPorts::ColorA>().getData();
		auto& colorB = getInputDataPort<InputPorts::ColorB>().getData();
		auto& mixedColor = getOutputDataPort<OutputPorts::MixedColor>().getMutableData();

		mixedColor = factor * colorA + (1 - factor) * colorB;
	}

};

