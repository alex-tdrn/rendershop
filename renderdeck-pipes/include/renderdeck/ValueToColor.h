#pragma once
#include "renderdeck/Pipe.hpp"

#include <glm/glm.hpp>
#include <array>

class ValueToColor : public Pipe<ValueToColor, InputList<float>, OutputList<glm::vec3>>
{
public:
	static inline std::string const name = registerPipe<ValueToColor>("Value To Color");

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
		auto& value = getInputDataPort<InputPorts::Value>().getData();
		auto& color = getOutputDataPort<OutputPorts::Color>().getMutableData();

		color = {value, value, value};
	}

};

