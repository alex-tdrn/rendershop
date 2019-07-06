#pragma once
#include "renderdeck/Source.hpp"

#include <glm/glm.hpp>

class RandomColorSource : public Source<glm::vec3>
{	
public:
	struct OutputPort
	{
		enum
		{
			Color
		};
	};

protected:
	void update() const override 
	{
		auto& color = getOutputPort<OutputPort::Color>().getValue();
		color = {rand()% 256 / 256.0, rand() % 256 / 256.0, rand() % 256 / 256.0 };
	}

};