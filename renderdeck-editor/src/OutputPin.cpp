#include "OutputPin.h"
#include "InputPin.h"

#include "renderdeck/AbstractPipe.hpp"
#include "renderdeck/OutputDataPort.hpp"
#include <glm/glm.hpp>

OutputPin::OutputPin(AbstractDataPort* port)
	: AbstractPin(port)
{
}

bool OutputPin::canConnect(AbstractPin* inputPin)
{
	if(!dynamic_cast<InputPin*>(inputPin))
		return false;
	return inputPin->canConnect(this);
}

void OutputPin::connect(AbstractPin* inputPin)
{
	assert(dynamic_cast<InputPin*>(inputPin));

	static_cast<InputPin*>(inputPin)->connect(this);
}

void OutputPin::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Output);

	ImGui::Text(port->getName().c_str());

	auto o = dynamic_cast<OutputDataPort<glm::vec3> const*>(port);

	if(o)
	{
		auto const& output = o->get();
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
