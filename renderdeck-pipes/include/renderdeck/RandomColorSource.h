#pragma once
#include "renderdeck/DataSource.hpp"

#include <glm/glm.hpp>
#include <array>
#include <tuple>


template<>
struct OutputDataPorts<class RandomColorSource>
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

class RandomColorSource : public DataSource<RandomColorSource>
{	
public:
	static inline std::string const name = registerPipe<RandomColorSource>("Random Color Source");

protected:
	
	std::string const& getName() const override final
	{
		return name;
	}
		
	void update() const override final
	{
		auto& color = getOutputDataPort<OutputDataPorts<RandomColorSource>::Color>().getMutableData();
		color = {rand()% 256 / 256.0, rand() % 256 / 256.0, rand() % 256 / 256.0 };
	}

};