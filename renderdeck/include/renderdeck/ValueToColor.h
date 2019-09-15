#pragma once
#include "renderdeck/Pipe.hpp"

#include <glm/glm.hpp>
#include <array>

class ValueToColor : public Pipe<ValueToColor, InputList<float>, OutputList<glm::vec3>>
{
public:
	static inline std::string const name = registerPipelineElement<ValueToColor>("Value To Color");

	struct InputPorts
	{
		static inline std::array names = {
			"Value"
		};
		enum {
			Value
		};

	};
	struct OutputPorts
	{
		static inline std::array names = {
			"Color"
		};
		enum {
			Color
		};
	};


public:
	void update() const override
	{
		auto& value = getInputPort<InputPorts::Value>().getResource();
		auto& color = getOutputPort<OutputPorts::Color>().getMutableResource();

		color = {value, value, value};
	}

};

