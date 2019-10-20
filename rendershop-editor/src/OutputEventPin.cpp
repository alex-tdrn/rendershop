#include "OutputEventPin.h"

#include "rendershop/base/OutputEventPort.hpp"
#include <glm/glm.hpp>

OutputEventPin::OutputEventPin(OutputEventPort* port)
	: OutputPin(port), port(port)
{
}

void OutputEventPin::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Output);

	if(port->getTimesTriggered() > triggerCount)
	{
		animCounter = 120;
		triggerCount = port->getTimesTriggered();
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


	ImGui::Text(port->getName().c_str());

	ImGui::PopStyleColor();

	ax::NodeEditor::PinPivotSize({0, 0});

	ax::NodeEditor::EndPin();
}

ImVec2 OutputEventPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getName().c_str());
}
