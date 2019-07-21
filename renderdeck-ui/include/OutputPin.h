#pragma once
#include "AbstractPin.hpp"

#include <imgui_node_editor.h>
#include <map>

class AbstractOutputPort;

class OutputPin : public AbstractPin
{
private:
	static inline std::map<AbstractOutputPort const*, ax::NodeEditor::PinId> portMap;

private:
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
	void draw() override;
	ImVec2 calculateSize() const override;
	AbstractOutputPort const* getPort() const
	{
		return port;
	}
	
	bool connect(AbstractPin const* otherPin) const override;
};