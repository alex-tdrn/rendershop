#pragma once
#include "renderdeck/Pipe.hpp"

#include <glm/glm.hpp>
#include <array>

class ClearBackgroundSink : public Pipe<ClearBackgroundSink, InputResourceList<glm::vec3>, OutputResourceList<>>
{
public:
	static inline std::string const name = registerPipe<ClearBackgroundSink>("Clear Background Sink");
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

protected:
	void update() const override;

};

