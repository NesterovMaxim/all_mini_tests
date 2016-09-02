#include "time_test.h"

#include <memory>

#define ARR_SIZE 10000000

char arr_plain[ARR_SIZE];
char *arr_ptr[ARR_SIZE];

void plain_access()
{
	std::cout << "PLAIN\n";

	time_test tt;
	for ( int i = 0; i < ARR_SIZE; ++i )
	{
		int j = arr_plain[i];
	}
}

void ptr_access()
{
	std::cout << "PTR\n";


	for ( int i = 0; i < ARR_SIZE; ++i )
	{
		arr_ptr[i] = new char;
	}

	{
		time_test tt;
		for ( int i = 0; i < ARR_SIZE; ++i )
		{
			int j = *arr_ptr[i];
		}
	}

	for ( int i = 0; i < ARR_SIZE; ++i )
	{
		delete arr_ptr[i];
	}
}

int main()
{
	plain_access();
	ptr_access();

	std::cout << "READY!\n";
	std::getchar();

	return 0;
}