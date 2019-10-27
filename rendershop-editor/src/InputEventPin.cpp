#include "InputEventPin.h"
#include "OutputPin.h"
#include "Stylesheet.hpp"
#include "ImGuiUtilities.hpp"
#include "rendershop/base/OutputEventPort.hpp"
#include "rendershop/base/InputEventPort.hpp"


InputEventPin::InputEventPin(InputEventPort* port)
	: InputPin(port), port(port)
{
}

void InputEventPin::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Input);

	justTriggered = port->getTimesTriggered() > triggerCount;
	if(justTriggered)
		anchorOffset.play();

	ImGui::Text(port->getName().c_str());

	auto anchorPosition = calculateAnchorPosition();

	if(port->isConnected())
		ImGui::DrawDiamond(anchorPosition, 5, Stylesheet::getCurrentSheet().eventColor);
	else
		ImGui::DrawDiamond(anchorPosition, 5, {0, 0, 0, 1}, Stylesheet::getCurrentSheet().eventColor);

	ax::NodeEditor::PinPivotRect(anchorPosition, anchorPosition);

	ax::NodeEditor::EndPin();
}

ImVec2 InputEventPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getName().c_str());
}

void InputEventPin::drawLink()
{
	if(connection != nullptr)
	{
		ax::NodeEditor::Link(linkID, connection->getID(), id,
			Stylesheet::getCurrentSheet().eventColor, Stylesheet::getCurrentSheet().linkThickness);
		
		if(justTriggered)
		{
			ax::NodeEditor::Flow(linkID, Stylesheet::getCurrentSheet().eventColor);

			triggerCount = port->getTimesTriggered();
			justTriggered = false;
		}
	}
}
