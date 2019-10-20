#include "OutputPin.h"
#include "InputPin.h"

OutputPin::OutputPin(AbstractPort* port)
	: AbstractPin(port)
{
	for(auto connection : port->getConnections())
		if(auto pin = getPinForPort(connection); pin != nullptr)
			connect(pin);
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

	static_cast<InputPin*>(inputPin)->connect(this);
}
