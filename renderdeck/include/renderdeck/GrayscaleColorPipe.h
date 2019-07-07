#pragma once
#include "renderdeck/Pipe.hpp"

#include <glm/glm.hpp>

class GrayscaleColorPipe : public Pipe<Sink<glm::vec3>, Source<glm::vec3>>
{
public:
	struct InputPort
	{
		enum
		{
			Color
		};
	};

	struct OutputPort
	{
		enum
		{
			Color
		};
	};

public:
	void update() const override
	{
		auto const& inputColor = getInputPort<InputPort::Color>().getCachedValue();
		auto& outputColor = getOutputPort<OutputPort::Color>().getMutableValue();
		const glm::vec3 linearGrayscale = glm::vec3(0.2126, 0.7152, 0.0722);
		outputColor = glm::vec3(glm::dot(linearGrayscale, inputColor));
	}

};