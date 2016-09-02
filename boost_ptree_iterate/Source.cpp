
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


void main()
{
	{
		ptree pt;
		pt.add("subject.sha", "value");
		pt.put("subject.sha", "value1");
		pt.add("subject.path", "path");

		ptree pt2;
		pt.add_child("subject", pt2);
		std::stringstream ss;
		write_json(ss, pt);
		std::cout << ss.str() << "\n";

		for ( const auto& section : pt ) {
			std::cout << section.first << std::endl;
			for ( const auto& settings : section.second ) {
				if ( settings.second.empty() ) {
					std::cout << "\t" << settings.first << " -> " << settings.second.data() << std::endl;
				}
				else {
					std::cout << "\t" << settings.first << " -> " << "\n";
					for ( auto subsett : settings.second ) {
						std::cout << "\t\t" << subsett.second.data() << std::endl;
					}
				}
			}
		}

	}

    std::getchar();
}
