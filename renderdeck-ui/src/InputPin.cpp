#include "InputPin.h"
#include "OutputPin.h"

#include "renderdeck/ResourcePort.hpp"

InputPin::InputPin(AbstractResourcePort* port)
	: AbstractPin(port), linkID(uniqueID())
{
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

void InputPin::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Input);

	ImGui::Text(port->getName().c_str());

	ax::NodeEditor::PinPivotSize({ 0, 0 });

	ax::NodeEditor::EndPin();
}

ImVec2 InputPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getName().c_str());
}

void InputPin::drawLink()
{
	if(connection != nullptr)
		ax::NodeEditor::Link(linkID, id, connection->getID());
}
