#include "InputPin.h"
#include "UniqueID.hpp"
#include "renderdeck/AbstractPipeline.hpp"

InputPin::InputPin(AbstractInputPort* port)
	: port(port), id(uniqueID())
{
	portMap[port] = id;
}

InputPin::~InputPin()
{
	portMap.erase(port);
}

ax::NodeEditor::PinId InputPin::getIDForPort(AbstractInputPort const* port)
{
	if(portMap.find(port) != portMap.end())
		return portMap[port];
	return -1;
}

void InputPin::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Input);

	ImGui::Text(port->getPortName().c_str());

	//ImGui::ColorButton("GrayscaleColorPipe", { output.r, output.g, output.b, 1 }, ImGuiColorEditFlags_NoTooltip, ImVec2(32, 32));
	ax::NodeEditor::PinPivotSize({ 0, 0 });

	ax::NodeEditor::EndPin();
}

ImVec2 InputPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getPortName().c_str());
}
