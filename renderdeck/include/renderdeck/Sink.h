#pragma once
#include "Connection.h"

#include <vector>
#include <memory>

class Sink
{
private:
	std::vector<std::shared_ptr<Connection>> connections;

public:
	Sink() = default;
	Sink(Sink const&) = delete;
	Sink(Sink&&) = delete;
	Sink& operator=(Sink const&) = delete;
	Sink& operator=(Sink&&) = delete;
	virtual ~Sink() = default;

public:
	virtual void update() const = 0;

};
