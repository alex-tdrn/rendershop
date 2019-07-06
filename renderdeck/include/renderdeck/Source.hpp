#pragma once
#include "Resource.hpp"

#include <array>

template<std::size_t N>
class Source
{
protected:
	mutable std::array<Resource, N> outputs;
	
public:
	Source() = default;
	Source(Source const&) = delete;
	Source(Source&&) = delete;
	Source& operator=(Source const&) = delete;
	Source& operator=(Source&&) = delete;
	virtual ~Source() = default;

public:
	Resource const& get(int outputIndex) const
	{
		for(auto const& output : outputs)
		{
			if(output.getLastModificationTime().isReset())
			{
				update();
				break;
			}
		}
		return outputs[outputIndex];
	}
	virtual void update() const = 0;

};
