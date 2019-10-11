#include "renderdeck\ValueToColor.h"

void ValueToColor::update()
{
	auto& value = getInputDataPort<InputPorts::Value>().getData();
	auto& color = getOutputDataPort<OutputPorts::Color>().getMutableData();

	color = {value, value, value};
}
