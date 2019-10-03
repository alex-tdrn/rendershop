#pragma once
#include "renderdeck/Pipe.hpp"

#include <glm/glm.hpp>
#include <array>

class RandomColorSource : public Pipe<RandomColorSource, InputResourceList<>, OutputResourceList<glm::vec3>>
{	
public:
	static inline std::string const name = registerPipe<RandomColorSource>("Random Color Source");

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
		auto& color = getOutputResourcePort<OutputPorts::Color>().getMutableResource();
		color = {rand()% 256 / 256.0, rand() % 256 / 256.0, rand() % 256 / 256.0 };
	}

};