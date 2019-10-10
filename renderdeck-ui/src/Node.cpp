#include "Node.h"
#include "UIDebug.hpp"
#include "renderdeck/AbstractSink.hpp"
#include "renderdeck/AbstractSource.hpp"

#include <algorithm>

Node::Node(AbstractPipe* pipe)
	: pipe(pipe), id(uniqueID())
{
	inputPins.reserve(100);
	outputPins.reserve(100);

	if(auto sink = dynamic_cast<AbstractSink*>(pipe); sink != nullptr)
	{
		for(auto inputPort : sink->getInputDataPorts())
			inputPins.emplace_back(inputPort);
	}

	if(auto source = dynamic_cast<AbstractSource*>(pipe); source != nullptr)
	{
		{
			for(auto outputPin : source->getOutputDataPorts())
				outputPins.emplace_back(outputPin);
		}
	}
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
	float const titleWidth = ImGui::CalcTextSize(pipe->getName().c_str()).x;

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
	min.x -= nodeEditorStyle.NodePadding.x - nodeEditorStyle.NodeBorderWidth;
	min.y -= nodeEditorStyle.NodePadding.y - nodeEditorStyle.NodeBorderWidth;
	max.x += nodeEditorStyle.NodePadding.z - nodeEditorStyle.NodeBorderWidth;

	auto const& coreStyle = ImGui::GetStyle();
	max.x += contentsWidth;
	max.y += ImGui::GetTextLineHeight();
	auto color = ImGui::GetColorU32(coreStyle.Colors[ImGuiCol_TitleBgActive]);
	auto drawList = ax::NodeEditor::GetNodeBackgroundDrawList(id);
	drawList->AddRectFilled(min, max, color, nodeEditorStyle.NodeRounding, ImDrawCornerFlags_Top);

	if(titleOffset > 0)
		ImGui::Indent(titleOffset);

	ImGui::Text(pipe->getName().c_str());

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

void Node::drawInputLinks()
{
	for(auto& inputPin : inputPins)
		inputPin.drawLink();
}

