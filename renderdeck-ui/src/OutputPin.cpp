#include "OutputPin.h"
#include "InputPin.h"

#include "renderdeck/AbstractPipeline.hpp"
#include "renderdeck/OutputPort.hpp"
#include <glm/glm.hpp>

OutputPin::OutputPin(AbstractResourcePort* port)
	: AbstractPin(port)
{
}

void OutputPin::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Output);

	ImGui::Text(port->getName().c_str());

	auto o = dynamic_cast<OutputPort<glm::vec3> const*>(port);

	if(o)
	{
		auto const& output = o->getResource();
		ImGui::ColorButton("Caca", { output.r, output.g, output.b, 1 }, ImGuiColorEditFlags_NoTooltip, ImVec2(32, 32));
	}

	//ImGui::ColorButton("GrayscaleColorPipe", { output.r, output.g, output.b, 1 }, ImGuiColorEditFlags_NoTooltip, ImVec2(32, 32));
	ax::NodeEditor::PinPivotSize({ 0, 0 }); 

	ax::NodeEditor::EndPin();
}

ImVec2 OutputPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getName().c_str());
}
