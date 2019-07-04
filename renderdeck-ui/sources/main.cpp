#include "renderdeck/Profiler.h"

#include <iostream>


int main(int argc, char** argv)
{
	Profiler profiler;
	std::cout << profiler.getTest();
	return 0;
}