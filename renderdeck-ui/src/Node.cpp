#include "Node.h"
#include "renderdeck/AbstractPipeline.hpp"

#include <algorithm>

void Node::initialize()
{
	spacing = ImGui::CalcTextSize(pipelineElement->getTypeName().c_str()).x;

	if(pipelineElement->getAbstractInputPorts().size() > 0)
	{
		float inputsGroupWidth = 0;
		inputPins.reserve(pipelineElement->getAbstractInputPorts().size());
		for(auto inputPort : pipelineElement->getAbstractInputPorts())
		{
			inputPins.emplace_back(inputPort);
			inputsGroupWidth = std::max(inputsGroupWidth, inputPins.back().calculateSize().x);
		}
		spacing -= inputsGroupWidth;
		spacing -= ImGui::GetStyle().ItemSpacing.x;
	}

	if(pipelineElement->getAbstractOutputPorts().size() > 0)
	{
		float outputsGroupWidth = 0;
		outputPins.reserve(pipelineElement->getAbstractOutputPorts().size());
		for(auto outputPort : pipelineElement->getAbstractOutputPorts())
		{
			outputPins.emplace_back(outputPort);
			outputsGroupWidth = std::max(outputsGroupWidth, outputPins.back().calculateSize().x);
		}
		spacing -= outputsGroupWidth;
		spacing -= ImGui::GetStyle().ItemSpacing.x;
	}

	if(spacing < 0)
		spacing = 0;

	initialized = true;
}

void Node::draw()
{
	if(!initialized)
		initialize();
	ax::NodeEditor::BeginNode(id);
	ImGui::Text(pipelineElement->getTypeName().c_str());

	ImGui::BeginGroup();
	for(auto& inputPin : inputPins)
		inputPin.draw();
	ImGui::EndGroup();

	ImGui::SameLine();
	ImGui::Dummy({spacing, 0});
	ImGui::SameLine();

	ImGui::BeginGroup();
	for(auto& outputPin : outputPins)
		outputPin.draw();
	ImGui::EndGroup();

	/*ImGui::Dummy({ w.x - 32, w.y });
	ImGui::SameLine();
	ax::NodeEditor::BeginPin(uniqueId++, ax::NodeEditor::PinKind::Output);
	ImGui::ColorButton("GrayscaleColorPipe", { output.r, output.g, output.b, 1 }, ImGuiColorEditFlags_NoTooltip, ImVec2(32, 32));
	ax::NodeEditor::PinPivotSize({ 0, 0 });*/
	//ax::NodeEditor::EndPin();

	ax::NodeEditor::EndNode();
}