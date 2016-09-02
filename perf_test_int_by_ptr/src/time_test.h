#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>

class time_test
{
public:
	time_test()
	{
		m_dw = ::GetTickCount();
	}
	~time_test()
	{
		report();
	}

	void report()
	{
		DWORD	dw = GetTickCount() - m_dw;

		//log(profile) << dw << std::endl;

		if ( dw >= 1 )
		{
			std::cout << dw << std::endl;
		}
		/*else
		{
		if (!str.is_empty())_trace_file(sz_profiler_log, "!!![%s:%d] %d", str.ptr(), m_calls, dw);
		else _trace_file(sz_profiler_log, "!!![unknown:%d] %d", m_calls, dw);
		}
		m_dw = GetTickCount();*/
	}

public:
	DWORD	m_dw;
};
