#include "InputDataPin.h"
#include "OutputPin.h"
#include "rendershop/base/AbstractDataPort.hpp"

InputDataPin::InputDataPin(AbstractDataPort* port)
	: InputPin(port), port(port)
{
}

void InputDataPin::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Input);

	ImGui::Text(port->getName().c_str());

	ax::NodeEditor::PinPivotSize({0, 0});

	ax::NodeEditor::EndPin();
}

ImVec2 InputDataPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getName().c_str());
}

void InputDataPin::drawLink()
{
	if(connection != nullptr)
		ax::NodeEditor::Link(linkID, connection->getID(), id);
}
