#pragma once
#include "renderdeck/Source.hpp"

#include <glm/glm.hpp>

class RandomColorSource : public Source<glm::vec3>
{	
public:
	struct OutputPort
	{
		enum
		{
			Color
		};
	};

public:
	RandomColorSource() = default;
	RandomColorSource(RandomColorSource const&) = delete;
	RandomColorSource(RandomColorSource&&) = delete;
	RandomColorSource& operator=(RandomColorSource const&) = delete;
	RandomColorSource& operator=(RandomColorSource&&) = delete;
	~RandomColorSource() = default;

public:
	void update() const override 
	{
		auto m = getModificationGuard<OutputPort::Color>();
		m.value = {rand()% 256 / 256.0, rand() % 256 / 256.0, rand() % 256 / 256.0 };
	}

};