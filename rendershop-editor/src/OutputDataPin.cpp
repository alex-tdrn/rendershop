#include "OutputDataPin.h"

#include "rendershop/base/OutputDataPort.hpp"
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
	
	auto drawList = ImGui::GetWindowDrawList();
	auto min = ImGui::GetItemRectMin();
	auto max = ImGui::GetItemRectMax();
	auto h = max.y - min.y;
	auto x = max.x + 20;
	auto y = min.y + h / 2;

	drawList->AddCircle({x, y}, 5, ImGui::GetColorU32({1, 0, 0, 1}));
	drawList->AddCircleFilled({x, y}, 4, ImGui::GetColorU32({0, 0, 0, 1}));

	ax::NodeEditor::PinPivotRect({x, y}, {x, y});

	ax::NodeEditor::EndPin();
}

ImVec2 OutputDataPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getName().c_str());
}
