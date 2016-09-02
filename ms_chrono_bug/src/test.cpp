#define _USE_32BIT_TIME_T
#include <chrono>
#include <boost\chrono.hpp>

#include <thread>
#include <boost\thread.hpp>

#include <iostream>

int main()
{
	std::cout << "1\n";
	boost::this_thread::sleep_for(boost::chrono::seconds(1));

	std::cout << "2\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::cout << "3\n";

	return 0;
}
