#include "renderdeck\DecomposeColor.h"

void DecomposeColor::update()
{
	auto& color = getInputDataPort<InputPorts::Color>().getData();
	auto& r = getOutputDataPort<OutputPorts::R>().getMutableData();
	auto& g = getOutputDataPort<OutputPorts::G>().getMutableData();
	auto& b = getOutputDataPort<OutputPorts::B>().getMutableData();

	r = color.r;
	g = color.g;
	b = color.b;
}
