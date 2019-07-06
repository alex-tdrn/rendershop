#pragma once
#include "renderdeck/Sink.hpp"

#include <glm/glm.hpp>

class ClearBackgroundSink : public Sink<glm::vec3>
{
public:
	struct InputPort
	{
		enum
		{
			Color
		};
	};

protected:
	void update() const override;

};

