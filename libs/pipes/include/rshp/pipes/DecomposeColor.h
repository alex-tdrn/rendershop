#pragma once
#include "rshp/base/Pipe.hpp"

#include <glm/glm.hpp>
#include <array>

namespace rshp::pipes
{

	class DecomposeColor : public rshp::base::Pipe<DecomposeColor, 
		rshp::base::InputList<glm::vec3>, rshp::base::OutputList<float, float, float>>
	{
	public:
		struct InputPorts
		{
			static inline std::array names = {
				"Color"
			};
			enum {
				Color
			};

		};

		struct OutputPorts
		{
			static inline std::array names = {
				"R",
				"G",
				"B"
			};
			enum {
				R,
				G,
				B
			};
		};

	public:
		static inline std::string const name = registerPipe<DecomposeColor>("Decompose Colors");

	public:
		void update() override;

	};

}