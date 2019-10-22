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

	auto drawList = ImGui::GetWindowDrawList();
	auto min = ImGui::GetItemRectMin();
	auto max = ImGui::GetItemRectMax();
	auto h = max.y - min.y;
	auto x = min.x - 20;
	auto y = min.y + h / 2;

	drawList->AddCircle({x, y}, 5, ImGui::GetColorU32({0, 0, 1, 1}));
	drawList->AddCircleFilled({x, y}, 4, ImGui::GetColorU32({0, 0, 0, 1}));

	ax::NodeEditor::PinPivotRect({x, y}, {x, y});

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
