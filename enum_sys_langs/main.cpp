#include <windows.h>
#include <Winnls.h>
#include <iostream>
#include <string>

// Get language as string
bool GetLangStringFromLangId( DWORD dwLangID_i, std::string& csLang_o )
{
   const int MAX_BUFF_LEN = 10;
 
   const LCID lcidLang = MAKELCID( dwLangID_i, SORT_DEFAULT );
 
   TCHAR szCountryBuffer[MAX_BUFF_LEN] = { 0 };
 
   DWORD dwCount = ::GetLocaleInfo( lcidLang, LOCALE_SISO3166CTRYNAME, szCountryBuffer, MAX_BUFF_LEN );
 
   if( !dwCount )
   {
      return false;
   }
 
   csLang_o = szCountryBuffer;
 
   return true;
}


BOOL CALLBACK EnumUILanguagesProc(
  _In_ LPTSTR   lp_lang_string,
  _In_ LONG_PTR lParam
)
{
	std::string csLanguage;
	GetLangStringFromLangId( std::stoi(lp_lang_string, 0, 16), csLanguage );
	std::cout << csLanguage << std::endl;
	return TRUE;		
}

int main()
{
	std::cout << "Enum langs:\n";
	::EnumUILanguages(EnumUILanguagesProc, 0,0); 
	return EXIT_SUCCESS;
}
