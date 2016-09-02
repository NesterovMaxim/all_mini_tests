#include "../intface.h"

#include <iostream>
#define out std::cout

unsigned int foo_data::get_cnt() {
	static unsigned int cnt = 0;
	return ++cnt;
}

foo_data::foo_data() {
	current_cnt = get_cnt();
	out << "foo_data ctor: " << current_cnt << "\n";
	complex_data = "1234567890";
}
foo_data::foo_data(const foo_data& other) {
	current_cnt = get_cnt();
	out << "foo_data copy ctor: " << other.current_cnt << " -> " << current_cnt << "\n";
}
foo_data& foo_data::operator=(const foo_data& other) {
	out << "foo_data op = : " << other.current_cnt << " -> " << current_cnt << "\n";
	current_cnt = other.current_cnt;

	return *this;
}
foo_data::~foo_data() {
	out << "foo_data ~dtor: " << current_cnt << "\n";
}
