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

	ImGui::Text(port->getName().c_str());

	if(o)
	{
		auto const& output = o->get();
		ImGui::ColorButton("Caca", {output.r, output.g, output.b, 1}, ImGuiColorEditFlags_NoTooltip, ImVec2(32, 32));
	}

	ax::NodeEditor::PinPivotSize({0, 0});

	ax::NodeEditor::EndPin();
}

ImVec2 OutputDataPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getName().c_str());
}
