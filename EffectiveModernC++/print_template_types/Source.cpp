#include <iostream>
#include <boost\type_index.hpp>

using boost::typeindex::type_id_with_cvr;

template <typename T>
void print() {
	std::cout << "\tT     = " << type_id_with_cvr<T>().pretty_name() << std::endl; \

	std::cout << "=== END ===\n";
}

template <typename T, typename T2, typename... I>
void print() {
	std::cout << "\tT     = " << type_id_with_cvr<T>().pretty_name() << std::endl; \

	print<T2, I...>();
}

int main() {
	print<int, char, void, std::string>();

	std::getchar();
	return 0;
}