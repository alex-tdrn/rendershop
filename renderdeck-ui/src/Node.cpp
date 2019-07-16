#include "Node.h"
#include "UIUtilities.hpp"
#include "renderdeck/AbstractPipeline.hpp"

#include <algorithm>

void Node::initialize()
{
	float titleWidth = ImGui::CalcTextSize(pipelineElement->getTypeName().c_str()).x;
	float contentsWidth = minimumSpacing;
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

	spacing = std::max(titleWidth - contentsWidth, minimumSpacing);
	contentsWidth += spacing - minimumSpacing;
	titleOffset = (contentsWidth - titleWidth) / 2 - itemSpacing;

	ImVec2 padding = {ax::NodeEditor::GetStyle().NodePadding.x, ax::NodeEditor::GetStyle().NodePadding.y};
	//padding.x += ImGui::GetStyle().FramePadding.x;
	//padding.y += ImGui::GetStyle().FramePadding.y;
	//padding.x += ax::NodeEditor::GetStyle().NodePadding.x;
	//padding.y += ax::NodeEditor::GetStyle().NodePadding.y;
	titleRect = {
		ImGui::GetCursorPosX() - padding.x,
		ImGui::GetCursorPosY() - padding.y,
		ImGui::GetCursorPosX() + titleOffset,
		ImGui::GetCursorPosY() + 1.25f * ImGui::GetTextLineHeight()
	};
	initialized = true;
}

void Node::draw()
{
	ax::NodeEditor::BeginNode(id);
	if(!initialized)
		initialize();
	auto drawList = ax::NodeEditor::GetNodeBackgroundDrawList(id);
	if(titleOffset > 0)
	{
		//drawRectAtCursor(id, 0, 1, 1, titleOffset);
		ImGui::Dummy({ titleOffset, 0 });
		ImGui::SameLine();
		drawSpacingRect(drawList);
	}
	ImGui::Text(pipelineElement->getTypeName().c_str());
	drawItemRect(drawList, 1, 0, 1);

	/*ax::NodeEditor::GetNodeBackgroundDrawList(id)->AddRectFilled({titleRect.x, titleRect.y}, { titleRect.z, titleRect.w }, 
		ImGui::GetColorU32(ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive]), ax::NodeEditor::GetStyle().NodeRounding,
		ImDrawCornerFlags_Top);*/

	ImGui::BeginGroup();
	for(auto& inputPin : inputPins)
		inputPin.draw();
	ImGui::EndGroup();

	drawItemRect(drawList, 1, 0, 0);

	if(!inputPins.empty())
	{
		ImGui::SameLine();
		drawSpacingRect(drawList);
	}

	//drawRectAtCursor(id, 0, 1, 1, spacing);
	ImGui::Dummy({spacing, 0});
	drawItemRect(drawList, 1, 0, 1);

	if(!outputPins.empty())
	{
		ImGui::SameLine();
		drawSpacingRect(drawList);
	}

	ImGui::BeginGroup();
	for(auto& outputPin : outputPins)
		outputPin.draw();

	ImGui::EndGroup();
	drawItemRect(drawList, 0, 1, 0);

	ax::NodeEditor::EndNode();
	drawItemRect(drawList, 0, 0, 0.5);
	
}