#pragma once
#include "renderdeck/Timestamp.hpp"

template<typename T>
class OutputPort final
{
public:
	class ModificationGuard
	{
		private:
			OutputPort<T>& port;

		public:
			T& value;

		public:
			ModificationGuard() = delete;
			ModificationGuard(OutputPort<T>& port, T& value)
				: port(port), value(value)
			{

			}
			~ModificationGuard()
			{
				port.lastModificationTime.update();
			}
	};

private:
	T value;
	Timestamp lastModificationTime;

public:
	OutputPort() = default;
	OutputPort(OutputPort const&) = delete;
	OutputPort(OutputPort&& that)
	{
		this->value = std::move(that.value);
	}
	OutputPort& operator=(OutputPort const& that) = delete;
	OutputPort& operator=(OutputPort&& that)
	{
		this->value = std::move(that.value);
		lastModificationTime.update();
		return *this;
	}
	~OutputPort() = default;

public:
	OutputPort<T>::ModificationGuard getModificationGuard()
	{
		return {*this, value};
	}

	T const& getValue() const
	{
		return value;
	}

	Timestamp const& getLastModificationTime() const 
	{
		return lastModificationTime;
	}

};