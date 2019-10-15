#pragma once
#include "AbstractPin.hpp"

class OutputPin : public AbstractPin
{
private:
	int triggerCount = 0;
	int animCounter = 0;

public:
	OutputPin() = default;
	OutputPin(AbstractPort* port);
	OutputPin(OutputPin&&) = default;
	OutputPin(OutputPin const&) = delete;
	OutputPin& operator=(OutputPin&&) = default;
	OutputPin& operator=(OutputPin const&) = delete;
	~OutputPin() = default;

public:
	bool canConnect(AbstractPin* inputPin) final override;
	void connect(AbstractPin* inputPin) final override;
	void draw() override;
	ImVec2 calculateSize() const override;

};