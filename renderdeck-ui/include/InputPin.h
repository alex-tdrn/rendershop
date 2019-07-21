#pragma once
#include "AbstractPin.hpp"

class OutputPin;

class InputPin : public AbstractPin
{
public:
	InputPin() = default;
	InputPin(AbstractResourcePort* port);
	InputPin(InputPin&&) = default;
	InputPin(InputPin const&) = delete;
	InputPin& operator=(InputPin&&) = default;
	InputPin& operator=(InputPin const&) = delete;
	~InputPin() = default;

public:
	void draw() override;
	ImVec2 calculateSize() const override;

};