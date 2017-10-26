#pragma once

#include <Commctrl.h>

#include <sstream>

#include "ProcessData.h"
#include "utils.h"

class tray_helper_class
{
public:
	// non-static data members are initialized in order of declaration in the class definition! 
	// hwnd should be declared before corresponding pids!
	// see declaration below in the class
	tray_helper_class() :
		_is_win64(IsWow64() == TRUE),
		_tray_hwnd(find_tray_toolbar_window()),
		_tray_overflow_area_hwnd(find_tray_overflow_area_window()),
		_tray_main_pid(get_pid_by_hwnd(_tray_hwnd)),
		_tray_overflow_area_pid(get_pid_by_hwnd(_tray_overflow_area_hwnd))
	{
		_button_count_main = ::SendMessage(_tray_hwnd, TB_BUTTONCOUNT, 0, 0);
		_button_count_overflow_area = ::SendMessage(_tray_overflow_area_hwnd, TB_BUTTONCOUNT, 0, 0);

		//std::wstringstream ss;
		//ss << L"tray h = " << _tray_hwnd << L", tray pid = " << _tray_main_pid << "\n";
		//ss << L"ovtray h = " << _tray_overflow_area_hwnd << L", ovtray pid = " << _tray_overflow_area_pid << "\n";
		//ss << L"tray cnt = " << _button_count_main << L", ovtray cnt = " << _button_count_overflow_area << "\n";
		//MessageBox(0, ss.str().c_str(), L"Test Tray", MB_OK);		
	}
	int get_tray_button_count(){ return _button_count_main + _button_count_overflow_area; }
	HWND get_icon_parent_hwnd(const int ind)
	{
		int real_ind = ind;
		HWND hwnd = 0;
		bool not_overflow_area_operation = true;
		if (ind < _button_count_main)
		{
			hwnd = _tray_hwnd;
		}
		else if (ind >= _button_count_main &&
			ind < _button_count_overflow_area + _button_count_main)
		{
			not_overflow_area_operation = false;
			hwnd = _tray_overflow_area_hwnd;
			real_ind -= _button_count_main;
		}

		if (!hwnd) return hwnd;

		init_data_struct(not_overflow_area_operation);

		if (_is_win64)
		{
			::SendMessage(hwnd, TB_GETBUTTON, real_ind, (LPARAM)data64->GetData());
			data64->ReadData(&_butt64);
			data64->ReadData< TRAYDATA >(&tray, (LPCVOID)_butt64.dwData);
		}
		else
		{
			::SendMessage(hwnd, TB_GETBUTTON, real_ind, (LPARAM)data32->GetData());
			data32->ReadData(&_butt32);
			data32->ReadData< TRAYDATA >(&tray, (LPCVOID)_butt32.dwData);
		}

		deinit_data_struct();

		return tray.hwnd;
	}

	RECT get_button_rect(const int ind) {
		RECT result = { 0 };

		int real_ind = ind;
		HWND hwnd = 0;
		bool not_overflow_area_operation = true;
		if ( ind < _button_count_main ) {
			hwnd = _tray_hwnd;
		}
		//else if ( ind >= _button_count_main &&
		//		 ind < _button_count_overflow_area + _button_count_main ) {
		//	not_overflow_area_operation = false;
		//	hwnd = _tray_overflow_area_hwnd;
		//	real_ind -= _button_count_main;
		//}

		if ( !hwnd ) return result;

		RECT tray_rect = { 0 };
		decltype(RECT::left) tray_left_base = 0;
		if ( ::GetWindowRect(hwnd, &tray_rect) == TRUE ) {
			tray_left_base = tray_rect.left;
		}


		int pid = _tray_main_pid;
		auto data_ptr = new CProcessData<RECT>(pid);


		auto ret_code = ::SendMessage(hwnd, TB_GETITEMRECT, ind, (LPARAM)data_ptr->GetData());

		if ( ret_code == TRUE ) {
			data_ptr->ReadData(&result);
		}

		return result;
	}

private:
	static HWND find_tray_overflow_area_window()
	{
		HWND hWnd = ::FindWindow(L"NotifyIconOverflowWindow", NULL);
		if (hWnd)
		{
			hWnd = ::FindWindowEx(hWnd, NULL, L"ToolbarWindow32", NULL);
		}
		return hWnd;
	}
	static HWND find_tray_toolbar_window()
	{
		HWND hWnd = ::FindWindow(L"Shell_TrayWnd", NULL);
		if (hWnd)
		{
			hWnd = ::FindWindowEx(hWnd, NULL, L"TrayNotifyWnd", NULL);
			if (hWnd)
			{
				hWnd = ::FindWindowEx(hWnd, NULL, L"SysPager", NULL);
				if (hWnd)
				{
					hWnd = ::FindWindowEx(hWnd, NULL, L"ToolbarWindow32", NULL);
				}
			}
		}
		return hWnd;
	}

	void init_data_struct(const bool not_overflow_area_operation)
	{
		DWORD pid;
		if (not_overflow_area_operation)
		{
			pid = _tray_main_pid;
		}
		else
		{
			pid = _tray_overflow_area_pid;
		}

		if (_is_win64)
		{
			data32 = NULL;
			data64 = new CProcessData<TBBUTTON64>(pid);
		}
		else
		{
			data32 = new CProcessData<TBBUTTON32>(pid);
			data64 = NULL;
		}
	}

	void deinit_data_struct()
	{
		if (data32 != NULL){ delete data32; data32 = NULL; }
		if (data64 != NULL){ delete data64; data64 = NULL; }
	}

private:
	struct TRAYDATA
	{
		HWND hwnd;
		UINT uID;
		UINT uCallbackMessage;
		DWORD Reserved[2];
		HICON hIcon;
	};
	struct TBBUTTON32{
		int iBitmap;
		int idCommand;
		BYTE fsState;
		BYTE fsStyle;
		BYTE bReserved[2];          // padding for alignment
		DWORD_PTR dwData;
		INT_PTR iString;
	};
	struct TBBUTTON64 {
		int iBitmap;
		int idCommand;
		BYTE fsState;
		BYTE fsStyle;
		BYTE bReserved[6];          // padding for alignment
		DWORD_PTR dwData;
		INT_PTR iString;
	};

private:
	// declaration order is important — HWND before PIDs
	const HWND _tray_hwnd;
	const HWND _tray_overflow_area_hwnd;
	const DWORD _tray_main_pid;
	const DWORD _tray_overflow_area_pid;

	int _button_count_main;
	int _button_count_overflow_area;
	TRAYDATA tray;
	const bool _is_win64;

	TBBUTTON32 _butt32;
	TBBUTTON64 _butt64;

	CProcessData<TBBUTTON32> *data32;
	CProcessData<TBBUTTON64> *data64;
};