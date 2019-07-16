#pragma once
#include <imgui_node_editor.h>
#include <map>

class AbstractInputPort;
class OutputPin;

class InputPin
{
private:
	static inline std::map<AbstractInputPort const*, ax::NodeEditor::PinId> portMap;

private:
	ax::NodeEditor::PinId id = -1;
	AbstractInputPort* port = nullptr;

public:
	InputPin() = default;
	InputPin(AbstractInputPort* port);
	InputPin(InputPin&&) = default;
	InputPin(InputPin const&) = delete;
	InputPin& operator=(InputPin&&) = default;
	InputPin& operator=(InputPin const&) = delete;
	~InputPin();

public:
	static ax::NodeEditor::PinId getIDForPort(AbstractInputPort const* port);
	ax::NodeEditor::PinId getID() const
	{
		return id;
	}
	void draw();
	ImVec2 calculateSize() const;
	AbstractInputPort const* getPort() const
	{
		return port;
	}

};