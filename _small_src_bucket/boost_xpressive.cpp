#include <iostream>
#include <boost/xpressive/xpressive_static.hpp>
#include <boost/xpressive/xpressive_dynamic.hpp>


using namespace boost::xpressive;

const mark_tag path( 1 );
const mark_tag filename( 2 );

struct filter
{
  wsregex srex;

  filter()
  {
		const static mark_tag drive_letter( 3 );
		const static mark_tag environment_variable( 4 );
			srex = (//!as_xpr(L'"') >>
													(
														//(
															//(drive_letter=(~after(set[range(L'a',L'z') | range(L'A',L'Z')])>>(set[range(L'a',L'z') | range(L'A',L'Z')]>>L":")))|
															//*(environment_variable=( L'%' >> +set[range( L'a', L'z' ) | range( L'A', L'Z' ) | _d | L'(' | L')'] >> L'%' ))
														//)
														//>>
														//(+(+set[as_xpr(L'\\') | L'/'] >> +set[as_xpr(L'%') | L'~' | L'+' | L'-' | L'{' | L'}' | L'(' | L')' | _s | _w | L'.'])) 
														(
														 (filename=(+set[as_xpr( L'%' ) | L'~' | L'+' | L'-' | L'{' | L'}' | L'(' | L')' | _s | _w | L'.'])) >> (as_xpr(L'"'))|
														 (filename=(+set[as_xpr( L'%' ) | L'~' | L'+' | L'-' | L'{' | L'}' | L'(' | L')' | _w | L'.']))
														)
														//>>
														//(filename=
														//  (
														//    *set[as_xpr(L'\\') | L'/'] |
  												  //	  (+set[as_xpr(L'\\') | L'/'] >> +set[as_xpr(L'%') | L'~' | L'+' | L'-' | L'{' | L'}' | L'(' | L')' | _s | _w | L'.'])
													  //  )
														//)
													)>>
									(as_xpr(L' ') | eos)
									);
	}

  /// Does the string match?
  bool pred(const std::wstring &source)
  {
		std::wstring::const_iterator start = source.begin();
		const std::wstring::const_iterator end = source.end();

		boost::xpressive::wsmatch res;
		const bool result = boost::xpressive::regex_search( start, end, res, srex );

		std::wcout << res[path] << std::endl << res[filename] << std::endl;

		return result;
  }

};

void dofilter(std::wstring &inp,
              std::ostream &os)
{
  filter f;
	if (f.pred(inp))
	{
		 os<<"\ntrue\n";
	}
	else
	{
		 os<<"\nfalse\n";
	}
}

int main(int argc, const char **argv)
{
	std::wstring test = LR"(rdpclip)";
  dofilter(test,
           std::cout);
}
