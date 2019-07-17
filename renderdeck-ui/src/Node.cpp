#include "Node.h"
#include "UIDebug.hpp"
#include "renderdeck/AbstractPipeline.hpp"

#include <algorithm>

Node::Node(AbstractPipelineElement* element)
	: pipelineElement(element), id(uniqueID())
{
	for(auto inputPort : pipelineElement->getAbstractInputPorts())
		inputPins.emplace_back(inputPort);

	for(auto outputPin : pipelineElement->getAbstractOutputPorts())
		outputPins.emplace_back(outputPin);
}

void Node::initializeLayout()
{
	float const itemSpacing = ImGui::GetStyle().ItemSpacing.x;
	float const minimumCenterSpacing = 20;

	auto measurePinGroup = [&](auto& pins) {
		float pinGroupWidth = 0;
		if(pins.size() > 0)
		{
			for(auto const& pin : pins)
				pinGroupWidth = std::max(pinGroupWidth, pin.calculateSize().x);
			contentsWidth += pinGroupWidth + itemSpacing;
		}
		return pinGroupWidth;
	};

	float const inputGroupWidth = measurePinGroup(inputPins);
	float const outputGroupWidth = measurePinGroup(outputPins);
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
	contentsWidth += centerSpacing;

	layoutInitialized = true;
}

void Node::drawTitle()
{
	auto const& nodeEditorStyle = ax::NodeEditor::GetStyle();
	ImVec2 min = ImGui::GetCursorPos();
	ImVec2 max = min;
	min.x -= nodeEditorStyle.NodePadding.x;
	min.y -= nodeEditorStyle.NodePadding.y;
	max.x += nodeEditorStyle.NodePadding.z;

	auto const& coreStyle = ImGui::GetStyle();
	max.x += contentsWidth;
	max.y += ImGui::GetTextLineHeight();
	auto color = ImGui::GetColorU32(coreStyle.Colors[ImGuiCol_TitleBgActive]);
	auto drawList = ax::NodeEditor::GetNodeBackgroundDrawList(id);
	drawList->AddRectFilled(min, max, color, nodeEditorStyle.NodeRounding, ImDrawCornerFlags_Top);

	if(titleOffset > 0)
		ImGui::Indent(titleOffset);

	ImGui::Text(pipelineElement->getTypeName().c_str());

	if(titleOffset > 0)
		ImGui::Unindent(titleOffset);
}

void Node::drawInputs()
{
	if(inputPins.empty())
		return;
	ImGui::BeginGroup();
	for(auto& inputPin : inputPins)
		inputPin.draw();
	ImGui::EndGroup();
}

void Node::drawOutputs()
{
	if(outputPins.empty())
		return;
	ImGui::BeginGroup();
	for(auto& outputPin : outputPins)
		outputPin.draw();
	ImGui::EndGroup();
}

void Node::draw()
{
	ax::NodeEditor::BeginNode(id);
	auto drawList = ax::NodeEditor::GetNodeBackgroundDrawList(id);

	if(!layoutInitialized)
		initializeLayout();

	drawTitle();

	drawInputs();
	if(!inputPins.empty())
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
	if(!outputPins.empty())
		debug::drawItemRect(drawList);

	ax::NodeEditor::EndNode();
	debug::drawItemRect(drawList);

}

std::vector<Link> Node::getInputLinks() const
{
	std::vector<Link> links;

	for(auto const& inputPin : inputPins)
		links.emplace_back(inputPin.getPort(), inputPin.getPort()->getConnectedPort());

	return links;
}
