#pragma once
#include "renderdeck/AbstractDataSource.hpp"
#include "renderdeck/OutputDataPort.hpp"
#include "renderdeck/Utility.hpp"

template <typename...>
struct generateOutputPorts;

template <typename... Args>
struct generateOutputPorts<std::tuple<Args...>>
{
	using type = std::tuple<OutputDataPort<Args>...>;
};

template<typename>
struct OutputDataPorts;

template<typename Derived>
class DataSource : public AbstractDataSource
{
protected:
	mutable typename generateOutputPorts<typename OutputDataPorts<Derived>::types>::type outputDataPorts;

public:
	DataSource()
	{
		static_for_index(outputDataPorts, [&](auto& outputDataPort, int index) {
			AbstractDataSource::abstractOutputDataPorts.push_back(&outputDataPort);
			outputDataPort.setName(OutputDataPorts<Derived>::names[index]);
		});
	}
	DataSource(DataSource const&) = delete;
	DataSource(DataSource&&) = delete;
	DataSource& operator=(DataSource const&) = delete;
	DataSource& operator=(DataSource&&) = delete;
	virtual ~DataSource() = default;

public:
	template<int index>
	auto& getOutputDataPort() const
	{
		return std::get<index>(outputDataPorts);
	}

};