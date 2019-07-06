#pragma once
#include "Source.h"
#include "Color.h"

class RandomColorSource : public Source
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
	RandomColorSource()
	{
		outputs.emplace_back(std::make_unique<Color>());
	}
	RandomColorSource(RandomColorSource const&) = delete;
	RandomColorSource(RandomColorSource&&) = delete;
	RandomColorSource& operator=(RandomColorSource const&) = delete;
	RandomColorSource& operator=(RandomColorSource&&) = delete;
	~RandomColorSource() = default;

public:
	void update() const override 
	{
		Color* color = static_cast<Color*>(outputs[OutputPort::Color].get());
		*color = Color({rand()% 256 / 256.0, rand() % 256 / 256.0, rand() % 256 / 256.0 });
	}
	Color const* getOutputColor() const
	{
		return static_cast<Color const*>(get(RandomColorSource::OutputPort::Color));
	}

};