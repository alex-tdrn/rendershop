#pragma once

#include "renderdeck/AbstractInputEventPort.hpp"

template <typename F>
class InputEventPort final : public AbstractInputEventPort
{
private:
	F callable;

public:
	InputEventPort(F callable)
		: callable(callable)
	{

	}
	InputEventPort(InputEventPort const&) = delete;
	InputEventPort(InputEventPort&&) = default;
	InputEventPort& operator=(InputEventPort const& that) = delete;
	InputEventPort& operator=(InputEventPort&&) = default;
	~InputEventPort() = default;

public:
	void trigger() const final override
	{
		callable();
	}

	void operator()() const final override
	{
		trigger();
	}

};