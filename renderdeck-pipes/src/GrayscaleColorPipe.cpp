#include "renderdeck\GrayscaleColorPipe.h"

void GrayscaleColorPipe::update()
{
	auto const& inputColor = getInputDataPort<InputPorts::Color>().getData();
	auto& outputColor = getOutputDataPort<OutputPorts::Color>().getMutableData();
	const glm::vec3 linearGrayscale = glm::vec3(0.2126, 0.7152, 0.0722);
	outputColor = glm::vec3(glm::dot(linearGrayscale, inputColor));
}
