#pragma once

#include <Windows.h>

BOOL IsWow64();

DWORD get_pid_by_hwnd(const HWND hwnd);
