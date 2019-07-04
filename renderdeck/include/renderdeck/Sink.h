#pragma once
#include "renderdeck/Resource.h"

#include <memory>

class Sink : public Resource
{
protected:
	std::unique_ptr<Resource> input;

public:
	Sink() = default;
	Sink(Sink const&) = delete;
	Sink(Sink&&) = delete;
	Sink& operator=(Sink const&) = delete;
	Sink& operator=(Sink&&) = delete;
	virtual ~Sink() = default;


};
