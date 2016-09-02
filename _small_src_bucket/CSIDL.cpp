#include <iostream>
#include <windows.h>

#include "Shlobj.h"
#pragma comment(lib, "Shell32.lib")

#include <vector>
#include <string>

	inline
	bool get_special_folder_path( const int csidl, std::wstring &path )
	{
		static const DWORD buffer_size = MAX_PATH * 2;
		wchar_t sys_dir[buffer_size] = { 0 };
		if ( ::SHGetSpecialFolderPathW( NULL, sys_dir, csidl, FALSE ) == TRUE )
		{
			// SHGetSpecialFolderPath is not supported, so prefer to avoid even probability of error
			sys_dir[buffer_size - 1] = '\0';
			const size_t str_len = wcslen( sys_dir ) + 1; // include last \0
	
			_wcslwr_s( sys_dir, str_len );
	
			path = sys_dir;
		}
		else
		{
			const auto rc = ::GetLastError();
			std::cout << "[!] Unknown error occurred while retrieving known path by CSIDL:"
							<< rc << ", " << csidl;
			return false;
		}
	
		return true;
	}

int main()
{
				//vector of CSIDL's ids which will be resolved in common Windows places with apps links
				static const std::vector<int> CSIDL_paths = {CSIDL_DESKTOPDIRECTORY,
															CSIDL_COMMON_DESKTOPDIRECTORY,
															CSIDL_PROGRAMS,
															CSIDL_COMMON_PROGRAMS};

				{
					for ( const auto csidl : CSIDL_paths )
					{
						std::wstring csidl_path;
						if ( !get_special_folder_path( csidl, csidl_path ) )
						{
							continue;
						}
						std::wcout << "path:" << csidl_path << "\n";
					}
				}

				// vector of CSIDL's ids which will be resolved in Quick Launch Windows paths
				// here we should add path to CSIDL's path tail
				static const std::vector<int> quick_launch_paths = {CSIDL_APPDATA,
																	CSIDL_COMMON_APPDATA };
				static const std::wstring quick_launch = L"\\Microsoft\\Internet Explorer\\Quick Launch\\";
				static const std::wstring wow6432_part = L"\\Wow6432Node";

				{
					for ( const auto csidl : quick_launch_paths )
					{
						std::wstring csidl_path;
						if ( !get_special_folder_path( csidl, csidl_path ) )
						{
							continue;
						}
						std::wcout << "path:" << csidl_path << "\n";
					}
				}

	return 0;
}
