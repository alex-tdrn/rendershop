#pragma once
#include "renderdeck/Source.hpp"

#include <glm/glm.hpp>
#include <array>


class RandomColorSource : public Source<RandomColorSource, OutputList<glm::vec3>>
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

	void update() override;

};