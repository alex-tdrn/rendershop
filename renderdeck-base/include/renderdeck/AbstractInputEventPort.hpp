#pragma once

#include "renderdeck/InputPort.hpp"
#include "renderdeck/OutputEventPort.hpp"

class OutputEventPort;

class AbstractInputEventPort : public InputPort<OutputEventPort>
{
public:
	AbstractInputEventPort() = default;
	AbstractInputEventPort(AbstractInputEventPort const&) = delete;
	AbstractInputEventPort(AbstractInputEventPort&&) = delete;
	AbstractInputEventPort& operator=(AbstractInputEventPort const& that) = delete;
	AbstractInputEventPort& operator=(AbstractInputEventPort&&) = delete;
	~AbstractInputEventPort() = default;

public:
	virtual void operator()() = 0;

};