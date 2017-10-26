#include <iostream>
#include <boost\type_index.hpp>

using boost::typeindex::type_id_with_cvr;

class data_t {
public:
	data_t(int cnt) {
		std::cout << "common ctor: "<<cnt<<"\n";
	}
	data_t(const data_t& other) {
		std::cout << "copy ctor\n";
	}
	data_t(data_t&& other) {
		std::cout << "move ctor\n";
	}
	data_t operator+(const data_t& lhs) {
		std::cout << "oper +\n";
		return *this;
	}

	~data_t() {
		std::cout << "dtor\n";
	}
};

template <typename T>
void Test(const T& value, int cnt = 2) {
	if ( cnt == 0 ) return;
	std::cout << "call #" << cnt << std::endl;

	std::cout << "\got     = " << type_id_with_cvr<T>().pretty_name() << std::endl; \
	//Test(T(cnt) + T(cnt), --cnt);
	//Test(std::move(T(cnt)), --cnt);
	Test((T(cnt)), --cnt);
}

template <typename T>
void Test_uref(T&& value, int cnt = 2) {
	if ( cnt == 0 ) return;
	std::cout << "call #" << cnt << std::endl;

	//Test_uref(std::move(T(cnt)), --cnt);
	Test(T(cnt) + T(cnt), --cnt);
}

void lvalue() {
	std::cout << "====1\n";
	Test(data_t(2));

	//std::cout << "====2\n";
	//data_t d(2);
	//Test(d);
}

void uref() {
	std::cout << "++++1\n";
	Test_uref(data_t(2));

	//std::cout << "++++2\n";
	//data_t d(4);
	//Test_uref(d);
}

int main() {
	lvalue();
	//uref();

	std::getchar();
	return 0;
}