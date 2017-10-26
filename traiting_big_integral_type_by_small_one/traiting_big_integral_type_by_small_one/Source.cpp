#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>
using namespace std;

//it seems int type is minimall for implicit cases
//using big_t = unsigned int;
//using small_t = unsigned short;
using big_t = unsigned long long;
using small_t = ULONG;

int main() {
	big_t big = ~big_t(0);
	small_t small = ~small_t(0);
	bool flag = big > ~small_t(0);
	bool flag2 = big > small;
	
	auto result = (big & ~small_t(0));
	auto result2 = (big & small);
	
	cout << "big:   " << big << std::endl;
	cout << "small: " << small << std::endl;
	cout << "flags(implicit vs explicit): " << flag << " vs " << flag2 << std::endl;
	cout << "result(implicit vs explicit vs in-place): " << result << " vs " << result2 << " vs " << (big & ~small_t(0)) << std::endl;
	
	// your code goes here
	return 0;
}