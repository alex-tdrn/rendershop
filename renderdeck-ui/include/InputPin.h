#pragma once
#include "AbstractPin.hpp"

#include <imgui_node_editor.h>
#include <map>

class AbstractResourcePort;
class OutputPin;

class InputPin : AbstractPin
{
private:
	static inline std::map<AbstractResourcePort const*, ax::NodeEditor::PinId> portMap;

private:
	AbstractResourcePort* port = nullptr;

public:
	InputPin() = default;
	InputPin(AbstractResourcePort* port);
	InputPin(InputPin&&) = default;
	InputPin(InputPin const&) = delete;
	InputPin& operator=(InputPin&&) = default;
	InputPin& operator=(InputPin const&) = delete;
	~InputPin();

public:
	static ax::NodeEditor::PinId getIDForPort(AbstractResourcePort const* port);
	void draw() override;
	ImVec2 calculateSize() const override;
	AbstractResourcePort const* getPort() const
	{
		return port;
	}

	bool connect(AbstractPin const* otherPin) const override;
};