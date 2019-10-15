#include "InputPin.h"
#include "OutputPin.h"
#include "renderdeck/base/OutputEventPort.hpp"

InputPin::InputPin(AbstractPort* port)
	: AbstractPin(port), linkID(uniqueID())
{
}

bool InputPin::canConnect(AbstractPin* outputPin)
{
	if(!dynamic_cast<OutputPin*>(outputPin))
		return false;
	return port->canConnect(outputPin->getPort());
}

void InputPin::connect(AbstractPin* outputPin)
{
	assert(dynamic_cast<OutputPin*>(outputPin));
	assert(canConnect(outputPin));

	port->connect(outputPin->getPort());
	connection = static_cast<OutputPin*>(outputPin);
}

void InputPin::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Input);

	auto e = dynamic_cast<InputEventPort*>(port);

	if(e)
	{
		if(e->getTimesTriggered() > triggerCount)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, {1, 0.7, 0.7, 1});
			justTriggered = true;
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Text, {1, 0.5, 0.5, 1});
		}
	}

	ImGui::Text(port->getName().c_str());

	if(e)
		ImGui::PopStyleColor();

	ax::NodeEditor::PinPivotSize({ 0, 0 });

	ax::NodeEditor::EndPin();
}

ImVec2 InputPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getName().c_str());
}

void InputPin::drawLink()
{
	if(connection != nullptr)
	{
		
		auto e = dynamic_cast<InputEventPort*>(port);
		if(e)
		{
			ax::NodeEditor::Link(linkID, connection->getID(), id, {1, 0.5, 0.5, 1}, 2.0f);
			if(justTriggered)
			{
				ax::NodeEditor::Flow(linkID);
				triggerCount = e->getTimesTriggered();
				justTriggered = false;
			}
		}
		else
		{
			ax::NodeEditor::Link(linkID, connection->getID(), id);
		}
	}
}
