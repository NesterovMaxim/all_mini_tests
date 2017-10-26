#include <iostream>
#include <string>
#include <sstream>

#define BUG

struct template_arg {
	int some_var;
};

template <typename T>
struct bar {
	using argument_type = typename T;
	int argument_size = sizeof(T);

	std::string raw_arg;


	argument_type* get(int c) {
		std::cout << c <<"\n";

		if ( !raw_arg.size() ) {
			// first-time call
			raw_arg.resize(argument_size);
			void *header = (void*)&raw_arg[0];
			memset(header, 0, argument_size);
		}

        return (argument_type*)&raw_arg[0];
	}

	size_t append_argument(std::string const &raw) {
#ifdef BUG
		get(1);
#else
		std::cout << 1 << "\n";
#endif
		raw_arg.append(raw.begin(), raw.end());
		return raw.size();
	}

};

struct baz : public bar<template_arg> {
	baz(const std::string& data) {
		std::stringstream ss;
		ss << data;

		//in release:
		// 1) get address where write some_var to inside raw_arg
		// 2) pass string to append to raw_arg
		// 3) raw_arg size is to small, it will be moved to new memory location
		// 4) write rules size by old, invalid, address
		get(2)->some_var = append_argument(ss.str());
		//get(2)->some_var = append_argument(data); // the case is not buggy
		std::cout << (get(3)->some_var);
	}
};


int main() {
	std::string s(12, '1');
	baz t(s);

	std::getchar();
	return 0;
}