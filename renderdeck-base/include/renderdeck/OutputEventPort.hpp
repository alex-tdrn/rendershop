#pragma once

#include "renderdeck/OutputPort.hpp"
#include "renderdeck/InputEventPort.hpp"

class InputEventPort;

class OutputEventPort final :  public OutputPort<InputEventPort>
{
public:
	OutputEventPort() = default;
	OutputEventPort(OutputEventPort const&) = delete;
	OutputEventPort(OutputEventPort&&) = default;
	OutputEventPort& operator=(OutputEventPort const& that) = delete;
	OutputEventPort& operator=(OutputEventPort&&) = default;
	~OutputEventPort() = default;

public:
	void trigger() const
	{
		for(auto connection : connections)
			connection->trigger();
	}
	void operator()() const
	{
		trigger();
	}

};