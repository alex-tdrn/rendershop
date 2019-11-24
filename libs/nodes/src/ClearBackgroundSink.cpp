#include "rshp/nodes/ClearBackgroundSink.h"

#include <glad/glad.h>

void rshp::nodes::ClearBackgroundSink::update()
{
	auto const& color = getInputData<InputPorts::Color>();
	glClearColor(color.r, color.g, color.b, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}