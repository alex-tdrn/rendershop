#include "Link.h"
#include "UniqueID.hpp"
#include "InputPin.h"
#include "OutputPin.h"

Link::Link(AbstractResourcePort const* inputPort, AbstractResourcePort const* outputPort)
	: inputPort(inputPort), outputPort(outputPort), id(uniqueID())
{
	inputPinID = InputPin::getIDForPort(inputPort);
	outputPinID = OutputPin::getIDForPort(outputPort);
}

void Link::draw()
{
	ax::NodeEditor::Link(id, inputPinID, outputPinID);
}