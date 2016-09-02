#pragma once

#include <sstream>
#include <fstream>

#include <locale>
#include <codecvt>

class  logger_ex {
public:
	logger_ex( const char *file ) {
		log_name = file;
		stream.open(file);

		const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
		stream.imbue(utf8_locale);
	}

	~logger_ex() {
		stream.close();
	};

	std::wostream &get_stream() {
		return stream;
	}
private:
	std::wofstream	stream;
	const char			*log_name;
};

#define log( logger ) \
	logger.get_stream()
