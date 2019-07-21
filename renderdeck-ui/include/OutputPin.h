#pragma once
#include "AbstractPin.hpp"

class OutputPin : public AbstractPin
{
public:
	OutputPin() = default;
	OutputPin(AbstractResourcePort* port);
	OutputPin(OutputPin&&) = default;
	OutputPin(OutputPin const&) = delete;
	OutputPin& operator=(OutputPin&&) = default;
	OutputPin& operator=(OutputPin const&) = delete;
	~OutputPin() = default;

public:
	void draw() override;
	ImVec2 calculateSize() const override;

};