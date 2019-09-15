#pragma once
#include "renderdeck/Source.hpp"

#include <glm/glm.hpp>
#include <array>

class RandomColorSource : public Source<RandomColorSource, OutputList<glm::vec3>>
{	
public:
	static inline std::string const name = registerPipelineElement<RandomColorSource>("Random Color Source");

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

protected:

	void update() const override 
	{
		auto& color = getOutputPort<OutputPorts::Color>().getMutableResource();
		color = {rand()% 256 / 256.0, rand() % 256 / 256.0, rand() % 256 / 256.0 };
	}

};