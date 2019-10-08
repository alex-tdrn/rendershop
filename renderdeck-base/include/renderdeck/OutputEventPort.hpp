#pragma once

#include "renderdeck/OutputPort.hpp"
#include "renderdeck/AbstractInputEventPort.hpp"

class AbstractInputEventPort;

class OutputEventPort :  public OutputPort<AbstractInputEventPort>
{
public:
	OutputEventPort() = default;
	OutputEventPort(OutputEventPort const&) = delete;
	OutputEventPort(OutputEventPort&&) = delete;
	OutputEventPort& operator=(OutputEventPort const& that) = delete;
	OutputEventPort& operator=(OutputEventPort&&) = delete;
	~OutputEventPort() = default;

public:
	void operator()()
	{
		for(auto connection : connections)
			connection->operator()();
	}

};