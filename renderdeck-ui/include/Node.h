#pragma once

class AbstractPipelineElement;

class Node
{
private:
	int id = -1;
	AbstractPipelineElement* pipelineElement = nullptr;

public:
	void draw();
};