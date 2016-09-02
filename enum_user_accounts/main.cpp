#include <windows.h>
#include <lm.h>

#pragma comment(lib, "netapi32.lib")

#include <iostream>

int main()
{
	LPBYTE buff;
	DWORD users_count = 0;
	DWORD dumb = 0;
	USER_INFO_1* ptr = nullptr;
	auto ret = ::NetUserEnum(NULL, 
							 1,
							 FILTER_NORMAL_ACCOUNT,
							 &buff,
							 MAX_PREFERRED_LENGTH,
							 &users_count,
							 &dumb,
							 NULL);
	if ( ret == NERR_Success )
	{
		ptr = (USER_INFO_1*)buff;
		int ctr = 0;
		while ( ctr < users_count )
		{
			std::wcout << ptr->usri1_name << "\n";
			const auto fl = ptr->usri1_flags;
			std::cout << std::hex << (fl & UF_NORMAL_ACCOUNT) << std::endl;
			std::cout << (fl & UF_ACCOUNTDISABLE) << std::endl;
			std::cout << (fl & UF_PASSWD_NOTREQD) << std::endl;
			if ( (fl & UF_NORMAL_ACCOUNT) &&
				 !(fl & UF_ACCOUNTDISABLE)) //&&
				 //!(fl & UF_PASSWD_NOTREQD) )
			{
				std::cout << "Normal account\n";
			}
			ptr++;
			ctr++;
			std::cout << std::endl;
		}
		::NetApiBufferFree(buff);
		std::cout << "Total users: " << users_count;
	}
	else
	{
		std::cout << "error occurred!";
		//::NetApiBufferFree(buff);// ERROR_MORE_DATA
	}
	return EXIT_SUCCESS;
}