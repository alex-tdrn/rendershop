#include "Node.h"
#include "UIUtilities.hpp"
#include "renderdeck/AbstractPipeline.hpp"

#include <algorithm>

void Node::initialize()
{
	float const itemSpacing = ImGui::GetStyle().ItemSpacing.x;
	float const minimumCenterSpacing = 20;
	float contentsWidth = 0;

	auto initializePinGroup = [&](auto& uiPins, auto& logicalPins) {
		float pinGroupWidth = 0;
		if(logicalPins.size() > 0)
		{
			uiPins.reserve(logicalPins.size());
			for(auto inputPort : logicalPins)
			{
				uiPins.emplace_back(inputPort);
				pinGroupWidth = std::max(pinGroupWidth, uiPins.back().calculateSize().x);
			}
			contentsWidth += pinGroupWidth + itemSpacing;
		}
		return pinGroupWidth;
	};

	float const inputGroupWidth = initializePinGroup(inputPins, pipelineElement->getAbstractInputPorts());
	float const outputGroupWidth = initializePinGroup(outputPins, pipelineElement->getAbstractOutputPorts());
	float const titleWidth = ImGui::CalcTextSize(pipelineElement->getTypeName().c_str()).x;

	if(titleWidth > contentsWidth + minimumCenterSpacing)
	{
		centerSpacing = titleWidth - contentsWidth;
	}
	else
	{
		centerSpacing = minimumCenterSpacing;
		titleOffset = (contentsWidth + centerSpacing - titleWidth) / 2;
	}

	initialized = true;
}

void Node::drawTitle()
{
	if(titleOffset > 0)
		ImGui::Indent(titleOffset);

	ImGui::Text(pipelineElement->getTypeName().c_str());

	if(titleOffset > 0)
		ImGui::Unindent(titleOffset);
}

void Node::drawInputs()
{
	ImGui::BeginGroup();
	for(auto& inputPin : inputPins)
		inputPin.draw();
	ImGui::EndGroup();
}

void Node::drawOutputs()
{
	ImGui::BeginGroup();
	for(auto& outputPin : outputPins)
		outputPin.draw();
	ImGui::EndGroup();
}

void Node::draw()
{
	ax::NodeEditor::BeginNode(id);
	auto drawList = ax::NodeEditor::GetNodeBackgroundDrawList(id);
	if(!initialized)
		initialize();

	drawTitle();

	drawInputs();
	debug::drawItemRect(drawList);

	if(!inputPins.empty())
	{
		ImGui::SameLine();
		debug::drawSpacingRect(drawList);
	}

	ImGui::Dummy({centerSpacing, 0});
	debug::drawItemRect(drawList);

	if(!outputPins.empty())
	{
		ImGui::SameLine();
		debug::drawSpacingRect(drawList);
	}

	drawOutputs();
	debug::drawItemRect(drawList);

	ax::NodeEditor::EndNode();
	debug::drawItemRect(drawList);

}