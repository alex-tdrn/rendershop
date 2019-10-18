#include "OutputPin.h"
#include "InputPin.h"

#include "rendershop/base/AbstractPipe.hpp"
#include "rendershop/base/OutputDataPort.hpp"
#include "rendershop/base/OutputEventPort.hpp"
#include <glm/glm.hpp>

OutputPin::OutputPin(AbstractPort* port)
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

	auto o = dynamic_cast<OutputDataPort<glm::vec3> const*>(port);
	auto e = dynamic_cast<OutputEventPort*>(port);

	if(e)
	{
		if(e->getTimesTriggered() > triggerCount)
		{
			animCounter = 120;
			triggerCount = e->getTimesTriggered();
		}
		if(animCounter > 0)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, {1, 0.7, 0.7, 1});
			animCounter--;
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Text, {1, 0.5, 0.5, 1});
		}

	}

	ImGui::Text(port->getName().c_str());

	if(e)
		ImGui::PopStyleColor();

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
