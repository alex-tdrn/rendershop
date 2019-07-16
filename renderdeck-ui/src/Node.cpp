#include "Node.h"
#include "UIUtilities.hpp"
#include "renderdeck/AbstractPipeline.hpp"

#include <algorithm>

void Node::initialize()
{
	static float const minimumPinGroupSpacing = 20;

	float contentsWidth = minimumPinGroupSpacing;
	float const itemSpacing = ImGui::GetStyle().ItemSpacing.x;

	auto initializePinGroup = [&](auto& uiPins, auto& logicalPins) {
		if(logicalPins.size() > 0)
		{
			float pinGroupWidth = 0;
			uiPins.reserve(logicalPins.size());
			for(auto inputPort : logicalPins)
			{
				uiPins.emplace_back(inputPort);
				pinGroupWidth = std::max(pinGroupWidth, uiPins.back().calculateSize().x);
			}
			contentsWidth += pinGroupWidth + itemSpacing;
		}
	};

	initializePinGroup(inputPins, pipelineElement->getAbstractInputPorts());
	initializePinGroup(outputPins, pipelineElement->getAbstractOutputPorts());

	float titleWidth = ImGui::CalcTextSize(pipelineElement->getTypeName().c_str()).x;
	pinGroupSpacing = std::max(titleWidth - contentsWidth, minimumPinGroupSpacing);
	contentsWidth += pinGroupSpacing - minimumPinGroupSpacing;
	titleOffset = (contentsWidth - titleWidth) / 2 - itemSpacing;

	initialized = true;
}

void Node::drawTitle()
{
	auto drawList = ax::NodeEditor::GetNodeBackgroundDrawList(id);

	if(titleOffset > 0)
	{
		drawRect(drawList, ImGui::GetCursorPos(), titleOffset);
		ImGui::Dummy({ titleOffset, 0 });
		ImGui::SameLine();
		drawSpacingRect(drawList);
	}
	ImGui::Text(pipelineElement->getTypeName().c_str());
	drawItemRect(drawList);
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
	drawItemRect(drawList);

	if(!inputPins.empty())
	{
		ImGui::SameLine();
		drawSpacingRect(drawList);
	}

	ImGui::Dummy({pinGroupSpacing, 0});
	drawItemRect(drawList);

	if(!outputPins.empty())
	{
		ImGui::SameLine();
		drawSpacingRect(drawList);
	}

	drawOutputs();
	drawItemRect(drawList);

	ax::NodeEditor::EndNode();
	drawItemRect(drawList);
}