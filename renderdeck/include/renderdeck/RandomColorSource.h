#pragma once
#include "renderdeck/Source.hpp"

#include <glm/glm.hpp>
#include <array>

class RandomColorSource : public Source<RandomColorSource, OutputList<glm::vec3>>
{	
public:
	static inline std::string const name = []() {
		std::string name = "Random Color Source";
		AbstractSource::sources[name] = []() {
			std::unique_ptr<AbstractSource> ptr = std::make_unique<RandomColorSource>();
			return ptr;
		};
		return name;
	}();

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