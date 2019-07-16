#include "OutputPin.h"
#include "UniqueID.hpp"

#include "renderdeck/AbstractPipeline.hpp"

OutputPin::OutputPin(AbstractOutputPort* port)
	: port(port), id(uniqueID())
{
	portMap[port] = id;
}

OutputPin::~OutputPin()
{
	portMap.erase(port);
}

ax::NodeEditor::PinId OutputPin::getIDForPort(AbstractOutputPort const* port)
{
	if(portMap.find(port) != portMap.end())
		return portMap[port];
	return -1;
}

void OutputPin::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Output);

	ImGui::Text(port->getPortName().c_str());

	//ImGui::ColorButton("GrayscaleColorPipe", { output.r, output.g, output.b, 1 }, ImGuiColorEditFlags_NoTooltip, ImVec2(32, 32));
	ax::NodeEditor::PinPivotSize({ 0, 0 }); 

	ax::NodeEditor::EndPin();
}

ImVec2 OutputPin::calculateSize() const
{
	return ImGui::CalcTextSize(port->getPortName().c_str());
}
