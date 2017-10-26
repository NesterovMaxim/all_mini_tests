#if 0
	class hkey_traits 
	{
	public:
		static void dealloc( HKEY &h ){
			if ( h )::RegCloseKey( h );
		}
	};

	template <typename T, typename Closer>
	struct windows_handle
	{
		typedef T handle_type;
		typedef Closer closer;
	private:
		struct impl
		{
			unsigned int refcount;

			handle_type m_handle;
		};

		void copy_from( const windows_handle &src )
		{
			assert( src.data != nullptr );

			data = src.data;
			data->refcount++;
		}

		void debug_log(const std::string &point) const
		{
			std::cout << point << " => " << std::hex << data->m_handle << std::dec << ", cnt::"<< data->refcount << "\n";
		}
	public:
		windows_handle(){}
		impl* data;

		T get_handle() const
		{
			assert( data != nullptr );
			assert( data->m_handle != 0);

			debug_log("get_handle()");

			return data->m_handle;
		}

		static windows_handle create( T svc_handle )
		{
			if ( svc_handle == NULL )
			{
				throw new std::exception( "You should pass non-null handle to windows_handle constructor!" );
			}

			windows_handle o;
			o.data = new impl();
			o.data->refcount = 1;
			o.data->m_handle = svc_handle;
			
			o.debug_log("create()");

			return o;
		}

		windows_handle( const windows_handle &src )
		{
			copy_from( src );
			debug_log("copy ctor()");
		}

		windows_handle& const operator=(const windows_handle &rhs)
		{
			copy_from( rhs );
			debug_log("op =()");
			return *this;
		}

		~windows_handle()
		{
			assert( data != nullptr );

			debug_log("dtor()");

			data->refcount--;
			
			if ( data->refcount == 0 )
			{
				closer::dealloc( data->m_handle );
				delete data;
			}
		}
	};
#endif