class dynamic_api 
{
private:
	dynamic_api() {
		checker_log()
			<< "dynamic_api: initializing...";

		ready = false;
		module = _load_system_library( _T( "Wintrust.dll" ) );

		if ( !module ) {
			checker_log()
				<< "dynamic_api: init error, can't load WINTRUST.DLL, err  = "
				<< ::GetLastError();
			return;
		}
		struct	{
			FARPROC &proc;
			const char *name;
		}
		import_table[] = {
			{ (FARPROC&)CryptCATAdminCalcHashFromFileHandle, "CryptCATAdminCalcHashFromFileHandle"},
			{ (FARPROC&)CryptCATAdminEnumCatalogFromHash, "CryptCATAdminEnumCatalogFromHash" },
		};

		bool	error = false;

		for ( int n = 0; n < sizeof( import_table ) / sizeof( *import_table ); ++n ) {
			import_table[n].proc = ::GetProcAddress( module, import_table[n].name );
			if ( !import_table[n].proc ) {
				checker_log()
					<< "dynamic_api: init error, can't get proc address for \""
					<< import_table[n].name
					<< "\"";
				error = true;
			}
		}

		if ( !error ) {
			ready = true;
			checker_log()
				<< "dynamic_api: initialized";
		}
	}

public:
	static dynamic_api& get_instance() {
		static dynamic_api	the;
		return the;
	}

	bool is_ready() const {
		return ready;
	}

//	typedef HANDLE	HCATINFO;

	BOOL (WINAPI *CryptCATAdminCalcHashFromFileHandle)( HANDLE hFile, DWORD* pcbHash, BYTE* pbHash, DWORD dwFlags );
	HCATINFO( WINAPI *CryptCATAdminEnumCatalogFromHash )(HCATADMIN hCatAdmin, BYTE* pbHash, DWORD cbHash, DWORD dwFlags, HCATINFO* phPrevCatInfo);

private:
	awin::auto_module		module;
	bool			ready;
	bool			extended_ready;
};
