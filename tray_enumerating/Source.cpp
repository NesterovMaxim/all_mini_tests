
#include <windows.h>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>

#include "trace_redirect.h"
#include "tray_helper_class.h"
#include "utils.h"

template < typename T >
struct enum_wnd_ctx
{
	enum_wnd_ctx(T search_by){ _search_by = search_by; }

	T get_search_by()const{ return _search_by; }
	std::set< HWND > result;

private:
	T _search_by;
};

struct hwnd_props
{
	std::wstring caption;
	bool has_no_gui;
	bool window_outside_desktop;
	bool too_small_window;
	size_t child_windows_count;
	std::map< HWND, std::wstring > child_wnd_classes;
};

struct app_window_status
{
	bool has_window;
	bool has_only_invisible_window;

	std::map< HWND, hwnd_props > top_windows_properties;
};

BOOL CALLBACK enum_wnd_proc(HWND hwnd, LPARAM lParam)
{
	enum_wnd_ctx<DWORD> *ctx = (enum_wnd_ctx<DWORD>*)lParam;
	const DWORD pid = ctx->get_search_by();
	DWORD lpdwProcessId;
	::GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	if (lpdwProcessId == pid)
	{
		ctx->result.insert(hwnd);
	}
	return TRUE;
}

BOOL CALLBACK enum_child_wnd_proc(HWND hwnd, LPARAM lParam)
{
	enum_wnd_ctx<HWND> *ctx = (enum_wnd_ctx<HWND>*)lParam;
	//const HWND ph = ctx->get_search_by();
	//if (hwnd == ph)
	{
		ctx->result.insert(hwnd);
	}
	return TRUE;
}

void enum_child_windows(const HWND h, std::map< HWND, std::wstring > &storage)
{
	enum_wnd_ctx<HWND> child_search_ctx(0);
	::EnumChildWindows(h, enum_child_wnd_proc, (LPARAM)&child_search_ctx);	

	for (const auto ch : child_search_ctx.result)
	{
		wchar_t class_name_buff[256] = { 0 };

		if (::GetClassName(ch, class_name_buff, 256) != 0)
		{
			std::wstring class_name = class_name_buff;
			if (class_name == L"#32770") class_name = L"Dialog";
			storage[ch] = class_name;
		}
		else storage[ch] = L"EMPTY";
	}
}

void check_coord( const HWND wndh, logger_ex &logger, const short size_treshold = 1 )
{
	RECT wr = { 0 };
	if ( ::GetWindowRect( wndh, &wr ) == TRUE )
	{
		const auto intersect_monitor = ::MonitorFromRect( &wr, MONITOR_DEFAULTTONULL );
		const bool outside_desktop = intersect_monitor == NULL;
		//log(logger) << (wr.right - dr.left) << " " << (dr.right - wr.left) << " " << (wr.bottom - dr.top) << " " << (dr.bottom - wr.top) << "\n";
		log( logger ) << "\t\t" << "outside_desktop :: " << outside_desktop << "\n";

		const bool is_too_small_window = (wr.right - wr.left) <= size_treshold && (wr.bottom - wr.top) <= size_treshold;
		//log(logger) << (wr.right - wr.left) << " " << (wr.bottom - wr.top) << "\n";
//		if (is_too_small_window)
			log( logger ) << "\t\t" << "too_small :: " << is_too_small_window << "\n\n";
	}
	else
	{
		log( logger ) << "Can't check is windows too small/outside desktop due win api error! Last error: " << ::GetLastError();
	}
}


bool check_tray(const DWORD pid)
{
	tray_helper_class tray_helper;

	const auto tray_buttons_total = tray_helper.get_tray_button_count();

	std::wstringstream ss;
	ss << L"Total icons at tray = " << tray_buttons_total << "\n";

	bool found = false;
	HWND app_hwnd = 0;
	for (int i = 0; i<tray_buttons_total; i++)
	{		
		app_hwnd = tray_helper.get_icon_parent_hwnd(i);
		const DWORD app_pid = get_pid_by_hwnd(app_hwnd);
		//ss << L"pid:" << app_pid << "\n";

		RECT rect = tray_helper.get_button_rect(i);
		//if ( ::GetWindowRect(app_hwnd, &rect) == TRUE ) {
			//std::wstringstream ss;
			//MessageBox(0, ss.str().c_str(), L"Test Tray", MB_OK);
		//}

		if ( app_pid == pid ) {
			ss << "\n t: " << rect.top << " r: " << rect.right << " l: " << rect.left;
			found = true;
			break;
		}
	}
	if ( found ) {

	}
	MessageBox(0, ss.str().c_str(), L"Test Tray", MB_OK);

	return found;
}

int main(int argc, char *argv[])
{

	if ( argc == 1 || argc > 2 )
	{
		std::cout << "use: cpw.exe pid\n";
		return EXIT_FAILURE;
	}

	const DWORD pid = atoi(argv[1]);
	//const short size_tr = (argc > 3) ? (atoi( argv[3] )) : 100;

	if (pid == 0 )
	{
		std::cout << "use: cpw.exe pid\n";
		return EXIT_FAILURE;
	}

	std::stringstream ss;
	ss << "report_" << pid << ".log";
	logger_ex logger( ss.str().c_str() );

	enum_wnd_ctx<DWORD> ctx((pid));
	::EnumWindows(enum_wnd_proc, (LPARAM)&ctx);

	app_window_status stats;

	// === has_window ===
	stats.has_window = ctx.result.size() > 0;

	// === has_only_invisible_window ===
	bool has_at_least_one_visible_window = false;	

	// === foreach by pid's windows ===
	for (const auto &h : ctx.result)
	{
		has_at_least_one_visible_window = has_at_least_one_visible_window || (::IsWindowVisible(h) == TRUE);

		// === caption ===
		wchar_t buff[1024];
		int chars_count = ::GetWindowText(h, buff, 1024);
		if (chars_count == 0) { buff[0] = '\0'; }
		stats.top_windows_properties[h].caption = buff;

		// === has_no_gui + child_windows_count ===
		enum_child_windows(h, stats.top_windows_properties[h].child_wnd_classes);

		stats.top_windows_properties[h].child_windows_count = stats.top_windows_properties[h].child_wnd_classes.size();
		stats.top_windows_properties[h].has_no_gui = stats.top_windows_properties[h].child_wnd_classes.size() == 0;
	}	
	stats.has_only_invisible_window = !has_at_least_one_visible_window; // <- it's should be there due checking in foreach above



	// ========= REPORT ==========	
	log(logger) << "pid :: " << pid << "\n";
	log( logger ) << "has_tray_icon :: " << check_tray( pid ) << "\n";
	log(logger) << "has_window :: " << std::boolalpha << stats.has_window << "\n";
	log(logger) << "has_only_invisible_window :: " << std::boolalpha << stats.has_only_invisible_window << "\n";
	log(logger) << "total top-windows count :: " << stats.top_windows_properties.size() << "\n";


	for (const auto &kv : stats.top_windows_properties)
	{
		const HWND h = kv.first;
		const std::wstring test = kv.second.caption;
		log(logger) << "\t" << std::hex << kv.first << std::dec << " -> " << "\n\t\t" << "caption :: \"" << kv.second.caption << "\"\n";

		wchar_t class_name_buff[256] = { 0 };
		if ( ::GetClassName( h, class_name_buff, 256 ) != 0 )
		{
			log( logger ) << "\t\t" << "class :: \"" << class_name_buff << "\"\n";
		}

		log(logger) << "\t\t" << "children count :: " << kv.second.child_windows_count << "\n";
		//log(logger) << "\t\t" << "has_no_gui :: " << kv.second.has_no_gui << "\n";

		check_coord( h, logger );

		for (const auto &kv : kv.second.child_wnd_classes)
		{			
			log(logger) << "\t\t" << std::hex << kv.first << " is \"" << kv.second << "\"\n";
		}
		log(logger) << std::dec;
	}

	std::cout << "\nready!\n";

	return EXIT_SUCCESS;
}
