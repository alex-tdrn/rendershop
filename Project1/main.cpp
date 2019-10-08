#include <iostream>
#include "renderdeck/OutputEventPort.hpp"
#include "renderdeck/InputEventPort.hpp"

void a()
{
	std::cout << "A\n";
}

class GGG
{
public:
	static void b()
	{
		std::cout << "B\n";
	}

	void c()
	{
		std::cout << "C\n";
	}
};

int main(int, char**)
{
	auto eventPort1 = InputEventPort(GGG::b);
	auto eventPort2 = InputEventPort(a);

	GGG g;

	auto eventPort3 = InputEventPort([&](){
		g.c();
	});
	
	OutputEventPort trigererererer;
	trigererererer.connect(&eventPort1);
	trigererererer.connect(&eventPort2);
	trigererererer.connect(&eventPort3);

	trigererererer();

	return 0;
}