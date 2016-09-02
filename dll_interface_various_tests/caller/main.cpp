#include "../intface.h"
#include <iostream>
#include <windows.h>

using namespace std;

// A factory of IKlass-implementing objects looks thus
typedef IKlass* (__cdecl *iklass_factory)();

using create_fun_ptr = TestClass_i*(*)();

int main()
{
	// Load the DLL
	HINSTANCE dll_handle = ::LoadLibrary( TEXT( "DllImpl.dll" ) );
	if ( !dll_handle ) {
		cerr << "Unable to load DLL!\n";
		return 1;
	}

	create_fun_ptr factory_func = reinterpret_cast<create_fun_ptr>(
		::GetProcAddress( dll_handle, "create_test_class" ));

	auto obj = factory_func();
	{
		std::shared_ptr<std::string> res;
		obj->get_string(res);
		std::cout << *res << std::endl;
	}

	//// Get the function from the DLL
	//iklass_factory factory_func = reinterpret_cast<iklass_factory>(
	//	::GetProcAddress( dll_handle, "create_klass" ));
	//if ( !factory_func ) {
	//	cerr << "Unable to load create_klass from DLL!\n";
	//	::FreeLibrary( dll_handle );
	//	return 1;
	//}

	//// Ask the factory for a new object implementing the IKlass
	//// interface
	//IKlass* instance_def = dynamic_cast< IKlass * >(factory_func());
	IKlass* instance_def = Klass::create();

	auto test_data = instance_def->get_data();
	delete test_data;

	//{
	//	auto std_type_var = instance_def->get_string();
	//	std::cout << std_type_var << std::endl;
	//}

	//{
	//	auto std_type_var = instance_def->get_wrapped_string();
	//	std::cout << std_type_var.data << std::endl;
	//}

	{
		auto std_type_ptr_var = instance_def->get_string_smart_ptr();
		std::cout << *std_type_ptr_var << std::endl;
	}

	{
		std::shared_ptr<std::string> std_type_ptr_var(instance_def->get_string_ptr());
		std::cout << *std_type_ptr_var << std::endl;
		//delete std_type_ptr_var;
	}

	//IKlass2* instance = dynamic_cast< IKlass2 * >(instance_def);
	//if ( instance == nullptr )
	//{
	//	cout << "using only v1\n";
	//}
	
	// Play with the object
	//int t = instance_def->do_stuff( 5 );
	//cout << "t = " << t << endl;
	//instance_def->do_something_else( 100.3 );
	//int t2 = instance_def->do_stuff( 0 );
	//cout << "t2 = " << t2 << endl;

	//if ( instance )
	//{
	//	instance->extension(t2);
	//	cout << "t2 = " << t2 << endl;
	//}

	// Destroy it explicitly
	instance_def->destroy();
	//::FreeLibrary( dll_handle );

	return 0;
}