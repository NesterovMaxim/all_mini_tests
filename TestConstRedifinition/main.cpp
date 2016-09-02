#include <iostream>

#include "definition.h"

extern void fun();

int main()
{
	fun();
	auto& j = i;
	//j += 1;

	std::cout << i;

	return 0;
}