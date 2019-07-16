#include "Node.h"
#include "UIUtilities.hpp"
#include "renderdeck/AbstractPipeline.hpp"

#include <algorithm>

void Node::initialize()
{
	static float const minimumInputOutputSpacing = 20;

	float titleWidth = ImGui::CalcTextSize(pipelineElement->getTypeName().c_str()).x;
	float contentsWidth = minimumInputOutputSpacing;
	float const itemSpacing = ImGui::GetStyle().ItemSpacing.x;

	if(pipelineElement->getAbstractInputPorts().size() > 0)
	{
		float inputsGroupWidth = 0;
		inputPins.reserve(pipelineElement->getAbstractInputPorts().size());
		for(auto inputPort : pipelineElement->getAbstractInputPorts())
		{
			inputPins.emplace_back(inputPort);
			inputsGroupWidth = std::max(inputsGroupWidth, inputPins.back().calculateSize().x);
		}
		contentsWidth += inputsGroupWidth + itemSpacing;
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
		contentsWidth += outputsGroupWidth + itemSpacing;
	}

	centralSpacing = std::max(titleWidth - contentsWidth, minimumInputOutputSpacing);
	contentsWidth += centralSpacing - minimumInputOutputSpacing;
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

	ImGui::Dummy({centralSpacing, 0});
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