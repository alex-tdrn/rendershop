#pragma once
#include <imgui_node_editor.h>

class AbstractInputPort;
class AbstractOutputPort;

class Link
{
private:
	ax::NodeEditor::LinkId id = -1;
	AbstractInputPort const* inputPort;
	AbstractOutputPort const* outputPort;
	ax::NodeEditor::PinId inputPinID = -1;
	ax::NodeEditor::PinId outputPinID = -1;

public:
	Link() = default;
	Link(AbstractInputPort const* inputPort, AbstractOutputPort const* outputPort);
	Link(Link&&) = default;
	Link(Link const&) = delete;
	Link& operator=(Link&&) = default;
	Link& operator=(Link const&) = delete;

public:
	void draw();

};