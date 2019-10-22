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

	auto drawList = ImGui::GetWindowDrawList();
	auto min = ImGui::GetItemRectMin();
	auto max = ImGui::GetItemRectMax();
	auto h = max.y - min.y;
	auto x = min.x - 20;
	auto y = min.y + h / 2;

	drawList->AddCircle({x, y}, 5, ImGui::GetColorU32({1, 0, 0, 1}));
	drawList->AddCircleFilled({x, y}, 4, ImGui::GetColorU32({0, 0, 0, 1}));

	ax::NodeEditor::PinPivotRect({x, y}, {x, y});

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
