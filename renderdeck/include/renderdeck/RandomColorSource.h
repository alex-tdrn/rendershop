#pragma once
#include "Source.hpp"
#include "Color.h"

class RandomColorSource : public Source<1>
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
		Color& color = static_cast<Color&>(outputs[OutputPort::Color]);
		color = Color({rand()% 256 / 256.0, rand() % 256 / 256.0, rand() % 256 / 256.0 });
	}
	Color const& getOutputColor() const
	{
		return static_cast<Color const&>(get(OutputPort::Color));
	}

};