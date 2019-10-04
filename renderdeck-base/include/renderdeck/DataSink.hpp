#pragma once
#include "renderdeck/AbstractDataSink.hpp"
#include "renderdeck/InputDataPort.hpp"
#include "renderdeck/Utility.hpp"

template <typename...>
struct generateInputPorts;

template <typename... Args>
struct generateInputPorts<std::tuple<Args...>>
{
	using type = std::tuple<InputDataPort<Args>...>;
};


template<typename T>
struct InputDataPorts;

template<typename Derived>
class DataSink : public AbstractDataSink
{
protected:
	mutable typename generateInputPorts<typename InputDataPorts<Derived>::types>::type inputDataPorts;

public:
	DataSink()
	{
		static_for_index(inputDataPorts, [&](auto& inputDataPort, int index) {
			AbstractDataSink::abstractInputDataPorts.push_back(&inputDataPort);
			inputDataPort.setName(InputDataPorts<Derived>::names[index]);
		});
	}
	DataSink(DataSink const&) = delete;
	DataSink(DataSink&&) = delete;
	DataSink& operator=(DataSink const&) = delete;
	DataSink& operator=(DataSink&&) = delete;
	virtual ~DataSink() = default;

public:
	void updateAllInputs() const override final
	{
		static_for(inputDataPorts, [](auto const& inputDataPort) {
			inputDataPort.update();
		});
	}

	template<int index>
	auto& getInputDataPort() const
	{
		return std::get<index>(inputDataPorts);
	}

};