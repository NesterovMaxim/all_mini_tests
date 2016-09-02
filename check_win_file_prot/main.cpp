#include <windows.h>
#include <Sfc.h>

#pragma comment(lib, "Sfc.lib")

#include <iostream>

int main()
{
	/*	c:\windows\system32\ntdll.dll
		c:\windows\system32\ntoskrnl.exe
	*/
	const static WCHAR* check_file = LR"(c:\windows\system32\ntdll.dll)";
	const static WCHAR* check_file_2 = LR"(c:\windows\system32\sfc.dll)";
	std::cout << "Is protected: " << (::SfcIsFileProtected( NULL, check_file ) != 0) << std::endl;
	std::cout << "Is protected 2: " << (::SfcIsFileProtected( NULL, check_file_2 ) != 0) << std::endl;


	PROTECTED_FILE_DATA data = {0};
	int cnt = 0;
	while ( ::SfcGetNextProtectedFile(NULL, &data) != 0 )
	{
		std::wcout << (::SfcIsFileProtected( NULL, data.FileName ) != 0)<< L"::" << data.FileName << L"\n";
		++data.FileNumber;
	}

	return 0;
}