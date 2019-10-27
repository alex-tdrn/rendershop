#include "OutputDataPin.h"
#include "rendershop/base/OutputDataPort.hpp"
#include "ImGuiUtilities.hpp"

#include <glm/glm.hpp>

OutputDataPin::OutputDataPin(AbstractDataPort* port)
	: OutputPin(port), port(port)
{
}

void OutputDataPin::draw()
{

	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Output);
	auto o = dynamic_cast<OutputDataPort<glm::vec3> const*>(port);
	ImGui::BeginGroup();
	ImGui::Text(port->getName().c_str());

	if(o)
	{
		auto const& output = o->get();
		ImGui::ColorButton("Caca", {output.r, output.g, output.b, 1}, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, ImVec2(32, 32));
	}
	ImGui::EndGroup();
	
	auto anchorPosition = calculateAnchorPosition();
	auto anchorColor = ImGui::ColorFromHash(port->getDataTypeHash());

	if(port->isConnected())
		ImGui::DrawCircle(anchorPosition, 5, anchorColor);
	else
		ImGui::DrawCircle(anchorPosition, 5, {0, 0, 0, 1}, anchorColor);

	ax::NodeEditor::PinPivotRect(anchorPosition, anchorPosition);

	ax::NodeEditor::EndPin();
}

ImVec2 OutputDataPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getName().c_str());
}
