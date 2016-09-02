#include <iostream>
#include <map>
#include <string>

int main()
{
		std::multimap<int, std::string> m;
		m.insert(std::make_pair(1, "A"));
		m.insert(std::make_pair(1, "B"));
		m.insert(std::make_pair(1, "C"));
		m.insert(std::make_pair(2, "0"));

		for(auto &mit : m)
		{
				std::cout << mit.first << "::" << mit.second << "\n";
		}
}
