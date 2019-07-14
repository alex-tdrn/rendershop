#pragma once
#include "renderdeck/Sink.hpp"

#include <glm/glm.hpp>

class ClearBackgroundSink : public Sink<ClearBackgroundSink, InputList<glm::vec3>>
{
public:
	struct InputPort
	{
		enum
		{
			Color
		};
	};
	static inline std::string const name = "Clear Background Sink";

protected:
	void update() const override;

};

