#pragma once
#include "AbstractPin.hpp"

#include <imgui_node_editor.h>
#include <map>

class AbstractResourcePort;

class OutputPin : public AbstractPin
{
private:
	static inline std::map<AbstractResourcePort const*, ax::NodeEditor::PinId> portMap;

private:
	AbstractResourcePort* port = nullptr;

public:
	OutputPin() = default;
	OutputPin(AbstractResourcePort* port);
	OutputPin(OutputPin&&) = default;
	OutputPin(OutputPin const&) = delete;
	OutputPin& operator=(OutputPin&&) = default;
	OutputPin& operator=(OutputPin const&) = delete;
	~OutputPin();

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