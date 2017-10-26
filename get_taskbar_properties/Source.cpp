#include <iostream>
#include "windows.h"
#include "shellapi.h"

int main()
{
	//::SHAppBarMessage(ABM_QUERYPOS, &appdata);
	
	GetSystemMetrics(SM_CXSCREEN);
	/*
	 * get taskbar height
	 * if it bottom and not hidden also add pip
	 * draw alert at bottom + taskbar height
	 */


	APPBARDATA appdata = {};
	appdata.cbSize = sizeof(APPBARDATA);
	//add_pip = appdata.uEdge == ABE_BOTTOM; //add pip only if taskbar at bottom edge

	::SHAppBarMessage(ABM_GETTASKBARPOS, &appdata);
	const auto taskbar_rect = appdata.rc;

	const bool is_autohide = ::SHAppBarMessage(ABM_GETSTATE, &appdata) != 0;

	//appdata.uEdge = ABE_LEFT;


	if ( appdata.uEdge == ABE_BOTTOM )
		std::cout << appdata.uEdge << std::endl;

	if ( appdata.rc.top == taskbar_rect.top )
		std::cout << appdata.uEdge << std::endl;


	//if (::SHAppBarMessage(ABM_GETSTATE, &appdata) == ABS_AUTOHIDE) {
	//	//ABM_GETSTATE //is autohide

	//}
}