#pragma once
#include "renderdeck/Pipe.hpp"

#include <glm/glm.hpp>
#include <array>



class GrayscaleColorPipe : public Pipe<GrayscaleColorPipe, InputList<glm::vec3>, OutputList<glm::vec3>>
{
public:
	static inline std::string const name = registerPipe<GrayscaleColorPipe>("Grayscale Color Pipe");
	struct InputPorts
	{
		static inline std::array names = {
			"Color"
		};
		enum
		{
			Color
		};
	};
	struct OutputPorts
	{
		static inline std::array names = {
			"Color"
		};
		enum
		{
			Color
		};
	};

public:

	void update() const override
	{
		auto const& inputColor = getInputDataPort<InputPorts::Color>().getData();
		auto& outputColor = getOutputDataPort<OutputPorts::Color>().getMutableData();
		const glm::vec3 linearGrayscale = glm::vec3(0.2126, 0.7152, 0.0722);
		outputColor = glm::vec3(glm::dot(linearGrayscale, inputColor));
	}

};