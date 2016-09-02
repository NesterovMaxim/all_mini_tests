#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

struct logger
{
	static logger* create_logger(){return new logger();}
	static int gid;
	logger(){id = ++gid; std::cout << "create "<<id<<"\n";}	
	logger(const logger& oth){id = ++gid; std::cout << "copy from "<<oth.id<<" to "<<id<<"\n";}	
	~logger(){std::cout << "destroy "<<id<<"\n";}	

	int id;
};
int logger::gid = 0;

struct res
{
  res& operator=(logger* d)
	{
			data.reset(d);
			return *this;
	}	
	boost::shared_ptr<logger> data;	
};

struct res_optional : public boost::optional<boost::shared_ptr<logger>>
{
  res_optional& operator=(logger* d)
	{
		//std::cout << "copy op#1\n";
			boost::optional<boost::shared_ptr<logger>>::operator=(boost::shared_ptr<logger>(d));
		//std::cout << "copy op#2\n";
			return *this;
	}	
};

res test()
{
		res result;
		result = logger::create_logger();
		return result;
}


res_optional test_opt()
{
		res_optional result;
		result = logger::create_logger();
		return result;
}

int main()
{
	auto result = test();
	std::cout << "\n\n\noptional\n\n";
	auto result_2 = test_opt();
	std::cout << "END\n";
		return 0;
}
