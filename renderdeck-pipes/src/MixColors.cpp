#include "renderdeck\MixColors.h"

void MixColors::update()
{
	auto& factor = getInputDataPort<InputPorts::Factor>().getData();
	auto& colorA = getInputDataPort<InputPorts::ColorA>().getData();
	auto& colorB = getInputDataPort<InputPorts::ColorB>().getData();
	auto& mixedColor = getOutputDataPort<OutputPorts::MixedColor>().getMutableData();

	mixedColor = factor * colorA + (1 - factor) * colorB;
}
