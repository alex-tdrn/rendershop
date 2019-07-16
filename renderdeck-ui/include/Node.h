#pragma once
#include "UniqueID.hpp"
#include "InputPin.h"
#include "OutputPin.h"

#include <imgui_node_editor.h>
#include <vector>

class AbstractPipelineElement;

class Node
{
private:
	bool initialized = false;
	float titleOffset = 0;
	float centralSpacing = 0;
	ax::NodeEditor::NodeId id = -1;
	AbstractPipelineElement* pipelineElement = nullptr;
	std::vector<InputPin> inputPins;
	std::vector<OutputPin> outputPins;

public:
	Node() = default;
	Node(AbstractPipelineElement* element)
		: pipelineElement(element), id(uniqueID())
	{
		
	}
	Node(Node&&) = default;
	Node(Node const&) = delete;
	Node& operator=(Node&&) = default;
	Node& operator=(Node const&) = delete;

private:
	void initialize();
	void drawTitle();
	void drawInputs();
	void drawOutputs();

public:
	void draw();

};