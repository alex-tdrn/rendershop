#pragma once
#include "UniqueID.hpp"

#include <imgui_node_editor.h>

class AbstractPipelineElement;

class Node
{
private:
	ax::NodeEditor::NodeId id = -1;
	AbstractPipelineElement* pipelineElement = nullptr;

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

public:
	void draw();

};