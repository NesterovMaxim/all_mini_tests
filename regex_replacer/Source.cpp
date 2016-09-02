#include <iostream>
#include <fstream>
#include <map>
#include <regex>

int main() {
	std::regex rx(R"([\w\d\:\(\)\.\\\s]+:\s+(\w*UMA_HISTOGRAM\w+)\(.+,\s*\"(.+)\".*)");

	std::string text = R"() 
  C:\work_space\1_code\browsec\hips\core\ycs\config\product_config.cpp(54):	SCOPED_UMA_HISTOGRAM_TIMER(get_core(), "Profiler.product_config.init");
  C:\work_space\1_code\browsec\hips\core\ycs\config\service_config_manager.cpp(524):	SCOPED_UMA_HISTOGRAM_TIMER(get_core(), "Profiler.service_config_manager.reload_rules");
  ...
)";
	//std::cout << std::regex_replace(text, rx, "$1 $2\n");

	std::map<std::string, std::string> res;
	std::smatch m;
	while ( std::regex_search(text, m, rx) ) {
		if ( m.size() != 3 ) {
			continue;
		}
		//std::cout << m[1] << " " << m[2] << std::endl;
		res[m[2]] = m[1];
		text = m.suffix().str();
	}

	int i = 0;
	std::fstream fs("out.txt", std::ios::out);
	for ( auto& p : res ) {
		std::cout << ++i << ": " << p.first << " " << p.second << std::endl;
		fs << "\"" << p.first << "\";\"" << p.second << "\"" << std::endl;
	}

	std::getchar();

	return 0;
}