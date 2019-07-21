#pragma once
#include "AbstractPin.hpp"

#include <imgui_node_editor.h>
#include <map>

class AbstractInputPort;
class OutputPin;

class InputPin : AbstractPin
{
private:
	static inline std::map<AbstractInputPort const*, ax::NodeEditor::PinId> portMap;

private:
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
	void draw() override;
	ImVec2 calculateSize() const override;
	AbstractInputPort const* getPort() const
	{
		return port;
	}

	bool connect(AbstractPin const* otherPin) const override;
};