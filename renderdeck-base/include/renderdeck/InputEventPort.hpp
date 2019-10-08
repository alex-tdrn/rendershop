#pragma once

#include "renderdeck/AbstractInputEventPort.hpp"

template <typename F>
class InputEventPort : public AbstractInputEventPort
{
private:
	F callable;

public:
	InputEventPort(F callable)
		: callable(callable)
	{

	}
	InputEventPort(InputEventPort const&) = delete;
	InputEventPort(InputEventPort&&) = delete;
	InputEventPort& operator=(InputEventPort const& that) = delete;
	InputEventPort& operator=(InputEventPort&&) = delete;
	~InputEventPort() = default;

public:
	void operator()()
	{
		callable();
	}

};