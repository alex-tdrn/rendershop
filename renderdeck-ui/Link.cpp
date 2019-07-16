#include "Link.h"
#include "UniqueID.hpp"
#include "InputPin.h"
#include "OutputPin.h"

Link::Link(AbstractInputPort const* inputPort, AbstractOutputPort const* outputPort)
	: inputPort(inputPort), outputPort(outputPort), id(uniqueID())
{
	inputPinID = InputPin::getIDForPort(inputPort);
	outputPinID = OutputPin::getIDForPort(outputPort);
}

void Link::draw()
{
	ax::NodeEditor::Link(id, inputPinID, outputPinID);
}