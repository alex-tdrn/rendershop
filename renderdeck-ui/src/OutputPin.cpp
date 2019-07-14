#include "OutputPin.h"
#include "renderdeck/AbstractPipeline.hpp"

void OutputPin::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Output);

	ImGui::Text(port->getPortName().c_str());

	//ImGui::ColorButton("GrayscaleColorPipe", { output.r, output.g, output.b, 1 }, ImGuiColorEditFlags_NoTooltip, ImVec2(32, 32));
	ax::NodeEditor::PinPivotSize({ 0, 0 }); 

	ax::NodeEditor::EndPin();
}

ImVec2 OutputPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getPortName().c_str());
}
