#include <sstream>
#include <iostream>

#include <boost/optional.hpp>

	template <typename T>
	struct complex_result
	{
		complex_result(){}
		complex_result(const complex_result& other)
		{
			m_warnings_stream.str(""); //clean
			m_warnings_stream << other.m_warnings_stream.str();
			m_data = other.m_data;
		}

		bool operator()()
		{
				return !!m_data;
		}

		T& operator*()
		{
			if ( m_data )
			{
				return *m_data;
			}
			else
			{
					throw std::runtime_error(m_warnings_stream.str());
			}
		}

		complex_result& operator=(const T& data)
		{
				m_data = data;
				
				return *this;
		}

		complex_result& operator=(const complex_result& other)
		{
			m_warnings_stream.str(""); //clean
			m_warnings_stream << other.m_warnings_stream.str(); 
			m_data = other.m_data;

			return *this;
		}
		complex_result& operator+=(const complex_result& rhs)
		{
			m_warnings_stream << rhs.m_warnings_stream.str(); 
			m_data = rhs.m_data;

			return *this;
		}
		complex_result& operator<<(complex_result& ss, const complex_result& other_result)
		{
			ss.m_warnings_stream << other_result.m_warnings_stream.str(); 

			return *this;
		}

		template <typename T>
		friend complex_result& operator<<(complex_result& ss, const T& data )
		{
				ss.m_warnings_stream << data << "\n";
				return ss;
		}

		
		std::string get_warnings(){return m_warnings_stream.str();}

		private:
			boost::optional<T> m_data;
			std::stringstream m_warnings_stream;
	};

complex_result<int> test(const bool create)
{
	complex_result<int> result;
		if ( create )
		{
			result << "Create the value";
				return result = 2;
		}
		else
		{
				result << "Didn't create anything";
		}

		result << "Complete";
		return result;
}

class wrapper
{
	std::wstringstream m_ss;
	public:
	std::wstring get_warnings(){return m_ss.str();}

		template <typename T>
		friend wrapper& operator<<(wrapper& ss, const T& data )
		{
				ss.m_ss << data << "\n";
				return ss;
		}
};

int main()
{
	wrapper wr;
	wr << 1;
	std::wcout << wr.get_warnings();

auto ret_1 = test(false);

std::cout << ret_1.get_warnings();

if ( ret_1() )
{
		*ret_1;
}

auto ret_2 = test(true);

if ( ret_2() )
{
		std::cout << ret_2.get_warnings();
		std::cout << *ret_2;
}

ret_2 << ret_1;
ret_1 += ret_2;

std::cout << "1: " << ret_1.get_warnings() << "__" << *ret_1;
std::cout << "2: " << ret_2.get_warnings() << "__" << *ret_2;

std::cout << "\nEND\n";

std::cout << ret_1;

	return 0;
}
