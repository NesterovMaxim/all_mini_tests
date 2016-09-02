#include <iostream>

#include <string>
#include <sstream>
#include <unordered_map>

struct printer {
	printer(const printer& other) {
		std::stringstream ss;
		ss << "copy from " << other.m_name;
		m_name = ss.str();
		std::cout << "printer copy Ctor: " << m_name << std::endl;
	}
	printer(std::string name):m_name(name) {
		std::cout << "printer Ctor: " << m_name << std::endl;
	}
	~printer() {
		std::cout << "printer Dtor: " << m_name << std::endl;
	}

	std::string m_name;
};

void foreach_const() {
	std::cout << "Creating container...\n";
	std::unordered_map<int, printer> data = { { 0, printer("0") } };
	//std::unordered_map<int, printer> data;
	data.insert(std::make_pair(0, printer("0")));

	std::cout << "\nIterating container explicit...\n";
	for ( const std::pair<int, printer> &m : data ) {
		std::cout << "\t" << m.first << " :: " << m.second.m_name << std::endl;
	}

	std::cout << "\nIterating container auto...\n";
	for ( const auto &m : data ) {
		std::cout << "\t" << m.first << " :: " << m.second.m_name << std::endl;
	}

	std::cout << "Finish!\n";
}

int main() {
	foreach_const();

	std::getchar();

	return 0;
}