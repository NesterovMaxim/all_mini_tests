#include <chrono>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <ctime>

inline
std::ostream& operator<<(std::ostream& ss, std::chrono::system_clock::time_point time_point) {
	const auto time_t_point = std::chrono::system_clock::to_time_t(time_point);
	ss << std::ctime(&time_t_point);
	return std::move(ss);
}


std::string print(const long long time_t) {
	//char buffer[26];
	//ctime_s(buffer, 26, &time_t);
	//buffer[24] = '\0';  // Removes the newline that is added

	//return buffer;
	return std::ctime(&time_t);
}

int main() {
	using namespace std::chrono;

	const auto test_chp = (system_clock::now() - hours(3));
	const auto now = system_clock::now();

	const auto time_t_checkpoint = system_clock::to_time_t(test_chp);
	const auto time_t_now = system_clock::to_time_t(now);

	//print_now();
	std::cout
		<< "0. time_t now: " << time_t_now << std::endl
		<< "0. time_t chk: " << time_t_checkpoint << std::endl
		<< "1. now ctime: " << [&time_t_now] {return std::ctime(&time_t_now); }() << std::endl
		<< "1. chk ctime: " << (std::ctime(&time_t_checkpoint))<<std::endl
		<< "2. now local: " << std::put_time(std::localtime(&time_t_now), "%c  \n")
		<< "2. chk local: " << std::put_time(std::localtime(&time_t_checkpoint), "%c  \n")
		<< "3. now print: " << print(time_t_now).c_str() << std::endl
		<< "3. chk print: " << print(time_t_checkpoint).c_str() << std::endl
		<< "4. now << :" << system_clock::now()
		<< "4. chk << :" << test_chp
		<< "5. elapsed(hrs): "
		<< (duration_cast<hours>(system_clock::now() - test_chp)).count();

	std::getchar();
	return 0;
}

