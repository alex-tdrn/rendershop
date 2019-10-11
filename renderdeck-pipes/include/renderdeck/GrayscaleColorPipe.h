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

	void update() override;

};