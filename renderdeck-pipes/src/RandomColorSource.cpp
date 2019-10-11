#include "renderdeck\RandomColorSource.h"

void RandomColorSource::update()
{
	auto& color = getOutputDataPort<OutputPorts::Color>().getMutableData();
	color = {rand() % 256 / 256.0, rand() % 256 / 256.0, rand() % 256 / 256.0};
}
