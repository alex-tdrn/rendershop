#pragma once

class Sink;
class Source;

struct Connection
{
	Source const* source;
	int outputPort;
	Sink const* sink;
	int inputPort;
};