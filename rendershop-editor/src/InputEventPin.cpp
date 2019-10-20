#include "InputEventPin.h"
#include "OutputPin.h"
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
		ImGui::PushStyleColor(ImGuiCol_Text, {1, 0.7, 0.7, 1});
	else
		ImGui::PushStyleColor(ImGuiCol_Text, {1, 0.5, 0.5, 1});

	ImGui::Text(port->getName().c_str());

	ImGui::PopStyleColor();

	ax::NodeEditor::PinPivotSize({0, 0});

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
		ax::NodeEditor::Link(linkID, connection->getID(), id, {1, 0.5, 0.5, 1}, 2.0f);
		if(justTriggered)
		{
			ax::NodeEditor::Flow(linkID);
			triggerCount = port->getTimesTriggered();
			justTriggered = false;
		}
	}
}
