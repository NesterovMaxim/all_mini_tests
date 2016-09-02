#include <iostream>
#include <windows.h>

int main()
{
	OSVERSIONINFO osvi = {0};
	bool bIsWindowsXPorLater = false;

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	::GetVersionEx(&osvi);

	std::cout << osvi.dwMajorVersion << ":min:" << osvi.dwMinorVersion << ":bnum:" << osvi.dwBuildNumber << "\n";


	DWORD dwVersion = 0; 
	DWORD dwMajorVersion = 0;
	DWORD dwMinorVersion = 0; 
	DWORD dwBuild = 0;

	dwVersion = GetVersion();

	// Get the Windows version.

	dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
	dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

	std::cout << dwMajorVersion << ":min:" << dwMinorVersion << "\n";

//	bIsWindowsXPorLater = 
//		 ( (osvi.dwMajorVersion > 5) ||
//		 ( (osvi.dwMajorVersion == 5) && (osvi.dwMinorVersion >= 1) ));

	return 0;
}
