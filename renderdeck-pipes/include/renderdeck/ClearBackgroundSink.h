#pragma once
#include "renderdeck/Sink.hpp"

#include <glm/glm.hpp>
#include <array>

class ClearBackgroundSink : public Sink<ClearBackgroundSink, InputList<glm::vec3>>
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
