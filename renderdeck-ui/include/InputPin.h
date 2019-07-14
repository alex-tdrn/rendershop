#pragma once
#include "UniqueID.hpp"

#include <imgui_node_editor.h>

class AbstractInputPort;

class InputPin
{
private:
	ax::NodeEditor::PinId id = -1;
	AbstractInputPort* port = nullptr;

public:
	InputPin() = default;
	InputPin(AbstractInputPort* port)
		: port(port), id(uniqueID())
	{

	}
	InputPin(InputPin&&) = default;
	InputPin(InputPin const&) = delete;
	InputPin& operator=(InputPin&&) = default;
	InputPin& operator=(InputPin const&) = delete;

public:
	void draw();
	ImVec2 calculateSize() const;

};