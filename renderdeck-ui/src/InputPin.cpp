#include "InputPin.h"
#include "renderdeck/AbstractPipeline.hpp"

void InputPin::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Input);

	ImGui::Text(port->getPortName().c_str());

	//ImGui::ColorButton("GrayscaleColorPipe", { output.r, output.g, output.b, 1 }, ImGuiColorEditFlags_NoTooltip, ImVec2(32, 32));
	ax::NodeEditor::PinPivotSize({ 0, 0 });

	ax::NodeEditor::EndPin();
}

ImVec2 InputPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getPortName().c_str());
}
