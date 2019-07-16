#pragma once
#include <imgui_node_editor.h>
#include <map>

class AbstractOutputPort;

class OutputPin
{
private:
	static inline std::map<AbstractOutputPort const*, ax::NodeEditor::PinId> portMap;

private:
	ax::NodeEditor::PinId id = -1;
	AbstractOutputPort* port = nullptr;

public:
	OutputPin() = default;
	OutputPin(AbstractOutputPort* port);
	OutputPin(OutputPin&&) = default;
	OutputPin(OutputPin const&) = delete;
	OutputPin& operator=(OutputPin&&) = default;
	OutputPin& operator=(OutputPin const&) = delete;
	~OutputPin();

public:
	static ax::NodeEditor::PinId getIDForPort(AbstractOutputPort const* port);
	ax::NodeEditor::PinId getID() const
	{
		return id;
	}
	void draw();
	ImVec2 calculateSize() const;
	AbstractOutputPort const* getPort() const
	{
		return port;
	}
	
};