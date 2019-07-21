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
	bool layoutInitialized = false;
	float contentsWidth = 0;
	float titleOffset = 0;
	float centerSpacing = 0;
	ax::NodeEditor::NodeId id = -1;
	AbstractPipelineElement* pipelineElement = nullptr;
	std::vector<InputPin> inputPins;
	std::vector<OutputPin> outputPins;

public:
	Node() = default;
	Node(AbstractPipelineElement* element);
	Node(Node&&) = default;
	Node(Node const&) = delete;
	Node& operator=(Node&&) = default;
	Node& operator=(Node const&) = delete;
	~Node() = default;

private:
	void initializeLayout();
	void drawTitle();
	void drawInputs();
	void drawOutputs();

public:
	void draw();
	void drawInputLinks();

};