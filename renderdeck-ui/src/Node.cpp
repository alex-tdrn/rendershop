#include "Node.h"
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

static void drawItemRect(ax::NodeEditor::NodeId id, float r, float g, float b)
{
	ax::NodeEditor::GetNodeBackgroundDrawList(id)->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(),
		ImGui::GetColorU32(ImVec4{r, g, b, 1}));	
}

static void drawItemSpacing(ax::NodeEditor::NodeId id)
{
	ax::NodeEditor::GetNodeBackgroundDrawList(id)->AddRect(
		{
			ImGui::GetCursorPosX() - ImGui::GetStyle().ItemSpacing.x,
			ImGui::GetCursorPosY(),
		}, {
			ImGui::GetCursorPosX(),
			ImGui::GetCursorPosY() + ImGui::GetTextLineHeight() + ImGui::GetStyle().ItemSpacing.y
		},
		ImGui::GetColorU32(ImVec4{ 1, 1, 0, 1 }))
		;
}

static void drawRectAtCursor(ax::NodeEditor::NodeId id, float r, float g, float b, float w)
{
	ax::NodeEditor::GetNodeBackgroundDrawList(id)->AddRect(
		{
			ImGui::GetCursorPosX(),
			ImGui::GetCursorPosY(),
		}, {
			ImGui::GetCursorPosX() + w,
			ImGui::GetCursorPosY() + ImGui::GetTextLineHeight()
		},
		ImGui::GetColorU32(ImVec4{ r, g, b, 1 }))
	;
}

void Node::draw()
{
	ax::NodeEditor::BeginNode(id);
	if(!initialized)
		initialize();
	if(titleOffset > 0)
	{
		drawRectAtCursor(id, 0, 1, 1, titleOffset);
		ImGui::Dummy({ titleOffset, 0 });
		ImGui::SameLine();
		drawItemSpacing(id);
	}
	ImGui::Text(pipelineElement->getTypeName().c_str());
	drawItemRect(id, 0, 0, 1);

	/*ax::NodeEditor::GetNodeBackgroundDrawList(id)->AddRectFilled({titleRect.x, titleRect.y}, { titleRect.z, titleRect.w }, 
		ImGui::GetColorU32(ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive]), ax::NodeEditor::GetStyle().NodeRounding,
		ImDrawCornerFlags_Top);*/

	ImGui::BeginGroup();
	for(auto& inputPin : inputPins)
		inputPin.draw();
	ImGui::EndGroup();
	drawItemRect(id, 1, 0, 0);

	if(!inputPins.empty())
	{
		ImGui::SameLine();
		drawItemSpacing(id);
	}
	drawRectAtCursor(id, 0, 1, 1, spacing);
	ImGui::Dummy({spacing, 0});
	if(!outputPins.empty())
	{
		ImGui::SameLine();
		drawItemSpacing(id);
	}

	ImGui::BeginGroup();
	for(auto& outputPin : outputPins)
		outputPin.draw();
	ImGui::EndGroup();
	drawItemRect(id, 0, 1, 0);

	/*ImGui::Dummy({ w.x - 32, w.y });
	ImGui::SameLine();
	ax::NodeEditor::BeginPin(uniqueId++, ax::NodeEditor::PinKind::Output);
	ImGui::ColorButton("GrayscaleColorPipe", { output.r, output.g, output.b, 1 }, ImGuiColorEditFlags_NoTooltip, ImVec2(32, 32));
	ax::NodeEditor::PinPivotSize({ 0, 0 });*/
	//ax::NodeEditor::EndPin();

	ax::NodeEditor::EndNode();
	drawItemRect(id, 0, 0, 0.5);
	ax::NodeEditor::GetNodeBackgroundDrawList(id)->AddRect(
		{
			ImGui::GetItemRectMin().x + ax::NodeEditor::GetStyle().NodePadding.x,
			ImGui::GetItemRectMin().y + ax::NodeEditor::GetStyle().NodePadding.y,
		},{	
			ImGui::GetItemRectMax().x - ax::NodeEditor::GetStyle().NodePadding.x,
			ImGui::GetItemRectMax().y - ax::NodeEditor::GetStyle().NodePadding.y,
		},
		ImGui::GetColorU32(ImVec4{ 0, 0, 0.75, 1 })
	);
}