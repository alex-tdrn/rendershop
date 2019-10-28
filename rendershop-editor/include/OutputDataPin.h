#pragma once
#include "OutputPin.h"

class AbstractDataPort;

class OutputDataPin final : public OutputPin
{
private:
	AbstractDataPort* port;

public:
	OutputDataPin() = default;
	OutputDataPin(AbstractDataPort* port);
	OutputDataPin(OutputDataPin&&) = default;
	OutputDataPin(OutputDataPin const&) = delete;
	OutputDataPin& operator=(OutputDataPin&&) = default;
	OutputDataPin& operator=(OutputDataPin const&) = delete;
	~OutputDataPin() = default;

public:
	void draw() override;
	ImVec2 calculateSize() const override;

};