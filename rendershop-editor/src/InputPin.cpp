#include "InputPin.h"
#include "OutputPin.h"

InputPin::InputPin(AbstractPort* port)
	: AbstractPin(port), linkID(uniqueID())
{
	auto connections = port->getConnections();
	assert(connections.size() <= 1);
	for(auto connection : connections)
		if(auto pin = getPinForPort(connection); pin != nullptr)
			connect(pin);
}

bool InputPin::canConnect(AbstractPin* outputPin)
{
	if(!dynamic_cast<OutputPin*>(outputPin))
		return false;
	return port->canConnect(outputPin->getPort());
}

void InputPin::connect(AbstractPin* outputPin)
{
	assert(dynamic_cast<OutputPin*>(outputPin));
	assert(canConnect(outputPin));

	port->connect(outputPin->getPort());
	connection = static_cast<OutputPin*>(outputPin);
}
