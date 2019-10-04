#pragma once
#include "renderdeck/DataSource.hpp"
#include "renderdeck/DataSink.hpp"

#include <glm/glm.hpp>
#include <array>

template<>
struct InputDataPorts<class GrayscaleColorPipe>
{
	using types = std::tuple<
		glm::vec3
	>;
	static inline std::array names = {
		"Color"
	};
	enum
	{
		Color
	};
};

template<>
struct OutputDataPorts<class GrayscaleColorPipe>
{
	using types = std::tuple<
		glm::vec3
	>;
	static inline std::array names = {
		"Color"
	};
	enum
	{
		Color
	};
};


class GrayscaleColorPipe : public DataSink<GrayscaleColorPipe>, DataSource<GrayscaleColorPipe>
{
public:
	static inline std::string const name = registerPipe<GrayscaleColorPipe>("Grayscale Color Pipe");

public:
	std::string const& getName() const override final
	{
		return name;
	}

	void update() const override
	{
		auto const& inputColor = getInputDataPort<InputDataPorts<GrayscaleColorPipe>::Color>().getData();
		auto& outputColor = getOutputDataPort<OutputDataPorts<GrayscaleColorPipe>::Color>().getMutableData();
		const glm::vec3 linearGrayscale = glm::vec3(0.2126, 0.7152, 0.0722);
		outputColor = glm::vec3(glm::dot(linearGrayscale, inputColor));
	}

};