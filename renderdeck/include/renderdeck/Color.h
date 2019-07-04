#pragma once
#include "renderdeck/Resource.h"
#include <glm/glm.hpp>

class Color : public Resource
{
private:
	glm::vec3 channels{1.0f, 1.0f, 1.0f};

public:
	Color() = default;
	Color(Color const&) = default;
	Color(glm::vec3 channels)
	{
		this->channels = channels;
	}
	Color(Color&&) = default;
	Color& operator=(Color const&) = default;
	Color& operator=(Color&&) = default;
	~Color() = default;
	
public:
	glm::vec3 const& getChannels() const
	{
		return channels;
	}

};