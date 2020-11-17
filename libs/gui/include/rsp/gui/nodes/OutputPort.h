#pragma once

#include "rsp/gui/Animation.hpp"
#include "rsp/gui/nodes/AbstractPort.hpp"

namespace rsp::gui
{
class OutputPort : public AbstractPort
{
public:
	OutputPort() = default;
	OutputPort(rsp::Port* port);
	OutputPort(OutputPort&&) = default;
	OutputPort(OutputPort const&) = delete;
	OutputPort& operator=(OutputPort&&) = default;
	OutputPort& operator=(OutputPort const&) = delete;
	virtual ~OutputPort() = default;

private:
	ImVec2 calculateAnchorPosition() const override;
	void drawContents() override;

public:
	bool canConnect(AbstractPort* inputPort) final override;
	void connect(AbstractPort* inputPort) final override;
};

} // namespace rsp::gui