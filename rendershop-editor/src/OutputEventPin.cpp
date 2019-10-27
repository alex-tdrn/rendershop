#include "OutputEventPin.h"
#include "Stylesheet.hpp"
#include "rendershop/base/OutputEventPort.hpp"
#include "ImGuiUtilities.hpp"

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
		anchorOffset.play();
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

	auto anchorPosition = calculateAnchorPosition();

	if(port->isConnected())
		ImGui::DrawDiamond(anchorPosition, 5, Stylesheet::getCurrentSheet().eventColor);
	else
		ImGui::DrawDiamond(anchorPosition, 5, {0, 0, 0, 1}, Stylesheet::getCurrentSheet().eventColor);

	ax::NodeEditor::PinPivotRect(anchorPosition, anchorPosition);

	ax::NodeEditor::EndPin();
}

ImVec2 OutputEventPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getName().c_str());
}
