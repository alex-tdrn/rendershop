#pragma once
#include "AbstractPin.hpp"

class OutputPin;

class InputPin : public AbstractPin
{
private:
	int triggerCount = 0;
	bool justTriggered = false;
	OutputPin* connection = nullptr;
	ax::NodeEditor::LinkId linkID = -1;

public:
	InputPin() = default;
	InputPin(AbstractPort* port);
	InputPin(InputPin&&) = default;
	InputPin(InputPin const&) = delete;
	InputPin& operator=(InputPin&&) = default;
	InputPin& operator=(InputPin const&) = delete;
	~InputPin() = default;

public:
	bool canConnect(AbstractPin* outputPin) final override;
	void connect(AbstractPin* outputPin) final override;
	void draw() final override;
	ImVec2 calculateSize() const final override;
	void drawLink();

};