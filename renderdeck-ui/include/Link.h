#pragma once
#include <imgui_node_editor.h>

class AbstractResourcePort;

class Link
{
private:
	ax::NodeEditor::LinkId id = -1;
	AbstractResourcePort const* inputPort;
	AbstractResourcePort const* outputPort;
	ax::NodeEditor::PinId inputPinID = -1;
	ax::NodeEditor::PinId outputPinID = -1;

public:
	Link() = default;
	Link(AbstractResourcePort const* inputPort, AbstractResourcePort const* outputPort);
	Link(Link&&) = default;
	Link(Link const&) = delete;
	Link& operator=(Link&&) = default;
	Link& operator=(Link const&) = delete;

public:
	void draw();

};