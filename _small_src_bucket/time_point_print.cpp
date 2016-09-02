template<typename Duration>
std::ostream &operator<<(std::ostream &stream,
						 const std::chrono::time_point<std::chrono::system_clock, Duration> &time_point) {
	const time_t time = std::chrono::system_clock::to_time_t(time_point);
	return stream << std::ctime(&time);
}
