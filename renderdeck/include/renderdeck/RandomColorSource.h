#pragma once
#include "renderdeck/Source.hpp"

#include <glm/glm.hpp>
#include <string>

class RandomColorSource : public Source<RandomColorSource, OutputList<glm::vec3>>
{	
public:
	struct OutputPort
	{
		enum
		{
			Color
		};
	};
	static inline std::string const name = "Random Color Source";

protected:

	void update() const override 
	{
		auto& color = getOutputPort<OutputPort::Color>().getMutableValue();
		color = {rand()% 256 / 256.0, rand() % 256 / 256.0, rand() % 256 / 256.0 };
	}

};