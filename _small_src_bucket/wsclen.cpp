#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <string>

int main()
{
   char* str1 = "Count.";
   wchar_t* wstr1 = L"Count.";
	 std::wstring wstr = L"Count.";

   // strlen gives the length of single-byte character string
   printf("Length of '%s' : %d\n", str1, strlen(str1) );

   // wstrlen gives the length of a wide character string
   wprintf(L"Length of '%s' : %d\n", wstr1, wcslen(wstr1) );

   wprintf(L"Length of '%s' : %d\n", wstr.c_str(), wstr.length() );

	return 0;
}
