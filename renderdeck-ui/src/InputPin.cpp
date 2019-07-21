#include "InputPin.h"
#include "OutputPin.h"
#include "UniqueID.hpp"
#include "renderdeck/AbstractPipeline.hpp"

InputPin::InputPin(AbstractInputPort* port)
	: AbstractPin(uniqueID()), port(port)
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

bool InputPin::connect(AbstractPin const* otherPin) const
{
	auto output = dynamic_cast<OutputPin const*>(otherPin);
	if(output == nullptr)
		return false;

	auto outputPort = output->getPort();

	return false;
}
