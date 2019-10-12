#pragma once

#include "renderdeck/InputPort.hpp"
#include "renderdeck/OutputEventPort.hpp"

#include <memory>

namespace detail
{
	class TypeErasedCallable
	{
	public:
		virtual void call() const = 0;

	};

	template <typename F>
	class Callable final : public TypeErasedCallable
	{
	private:
		F callable;

	public:
		Callable(F&& callable) : callable(callable){ }
		void call() const final override {	callable();	}

	};
}

class OutputEventPort;

class InputEventPort : public InputPort<OutputEventPort>
{
private:
	std::unique_ptr<detail::TypeErasedCallable> f;

public:
	template<typename F>
	InputEventPort(F&& callable)
		: f(std::make_unique<detail::Callable<F>>(std::forward<F>(callable)))
	{

	}
	InputEventPort(InputEventPort const&) = delete;
	InputEventPort(InputEventPort&&) = default;
	InputEventPort& operator=(InputEventPort const& that) = delete;
	InputEventPort& operator=(InputEventPort&&) = default;
	virtual ~InputEventPort() = default;

public:
	void trigger() const
	{
		f->call();
	}

	void operator()() const
	{
		trigger();
	}

};


