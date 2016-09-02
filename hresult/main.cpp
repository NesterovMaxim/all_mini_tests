#include <iostream>

#include <windows.h>


int main()
{
	HRESULT hr_E = OLE_E_FIRST;//S_FALSE;
	HRESULT hr_F = S_FALSE;

	if (FAILED( hr_E ))
		std::cout << "FAILED( hr_E )";
	else
		std::cout << "succ(hr_E)";

	if (FAILED( hr_F ))
		std::cout << "FAILED( hr_F )";
	else
		std::cout << "succ(hr_F)";
	return 0;
}
