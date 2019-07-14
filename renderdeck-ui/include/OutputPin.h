#pragma once
#include "UniqueID.hpp"

#include <imgui_node_editor.h>

class AbstractOutputPort;

class OutputPin
{
private:
	ax::NodeEditor::PinId id = -1;
	AbstractOutputPort* port = nullptr;

public:
	OutputPin() = default;
	OutputPin(AbstractOutputPort* port)
		: port(port), id(uniqueID())
	{

	}
	OutputPin(OutputPin&&) = default;
	OutputPin(OutputPin const&) = delete;
	OutputPin& operator=(OutputPin&&) = default;
	OutputPin& operator=(OutputPin const&) = delete;

public:
	void draw();
	ImVec2 calculateSize() const;

};