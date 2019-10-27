#include "OutputPin.h"
#include "InputPin.h"

OutputPin::OutputPin(AbstractPort* port)
	: AbstractPin(port)
{
	for(auto connection : port->getConnections())
		if(auto pin = getPinForPort(connection); pin != nullptr)
			connect(pin);
}

ImVec2 OutputPin::calculateAnchorPosition() const
{
	auto min = ImGui::GetItemRectMin();
	auto max = ImGui::GetItemRectMax();
	auto h = max.y - min.y;
	auto x = max.x + anchorOffset;
	auto y = min.y + h / 2;
	return {x, y};
}

bool OutputPin::canConnect(AbstractPin* inputPin)
{
	if(!dynamic_cast<InputPin*>(inputPin))
		return false;
	return inputPin->canConnect(this);
}

void OutputPin::connect(AbstractPin* inputPin)
{
	assert(dynamic_cast<InputPin*>(inputPin));

	dynamic_cast<InputPin*>(inputPin)->connect(this);
}
