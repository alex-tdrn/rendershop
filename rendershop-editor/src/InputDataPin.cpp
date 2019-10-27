#include "InputDataPin.h"
#include "OutputPin.h"
#include "rendershop/base/AbstractDataPort.hpp"
#include "ImGuiUtilities.hpp"
#include "Stylesheet.hpp"

InputDataPin::InputDataPin(AbstractDataPort* port)
	: InputPin(port), port(port)
{
}

void InputDataPin::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Input);

	ImGui::Text(port->getName().c_str());

	auto anchorPosition = calculateAnchorPosition();
	auto anchorColor = ImGui::ColorFromHash(port->getDataTypeHash());

	if(port->isConnected())
		ImGui::DrawCircle(anchorPosition, 5, anchorColor);
	else
		ImGui::DrawCircle(anchorPosition, 5, {0, 0, 0, 1}, anchorColor);

	ax::NodeEditor::PinPivotRect(anchorPosition, anchorPosition);

	ax::NodeEditor::EndPin();
}

ImVec2 InputDataPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getName().c_str());
}

void InputDataPin::drawLink()
{
	if(connection != nullptr)
	{
		ax::NodeEditor::Link(linkID, connection->getID(), id, 
			ImGui::ColorFromHash(port->getDataTypeHash()), Stylesheet::getCurrentSheet().linkThickness);
	}
}
