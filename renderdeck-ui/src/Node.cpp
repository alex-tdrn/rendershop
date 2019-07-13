#include "Node.h"

#include <imgui_node_editor.h>

void Node::draw()
{
	ax::NodeEditor::BeginNode(uniqueId);
	ImGui::Text("RandomColorSource");

	glm::vec3 output = source.getOutputPort<RandomColorSource::OutputPort::Color>().getCachedValue();
	ImVec2 w = ImGui::CalcTextSize("RandomColorSource");
	ImGui::Dummy({ w.x - 32, w.y });
	ImGui::SameLine();
	ax::NodeEditor::BeginPin(uniqueId++, ax::NodeEditor::PinKind::Output);
	ImGui::ColorButton("GrayscaleColorPipe", { output.r, output.g, output.b, 1 }, ImGuiColorEditFlags_NoTooltip, ImVec2(32, 32));
	ax::NodeEditor::PinPivotSize({ 0, 0 });

	ax::NodeEditor::EndPin();

	ax::NodeEditor::EndNode();
}