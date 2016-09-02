#include "../intface.h"
#include <iostream>
#include <windows.h>

using namespace std;


TestClass_i* create_test_class() {
	return new TestClass();
}

	void delete_string(const std::string* ptr) {
		delete ptr;
	}

bool TestClass::get_string(std::shared_ptr<std::string>& smart_ptr) {
	//auto src = std::make_shared<std::string>("smth");

	std::shared_ptr<std::string> src = std::shared_ptr<std::string>(new std::string("smth"));// , delete_string);
	smart_ptr = src;
	return true;
}

IKlass* Klass::create() {
		return new Klass();
	}

	Klass::Klass()
		: m_data( 0 )
	{
		cerr << "MyKlass constructor\n";
	}

	Klass::~Klass()
	{
		cerr << "MyKlass destructor\n";
	}

	void Klass::destroy()
	{
		delete this;
	}

	int Klass::do_stuff( int param )
	{
		m_data += param;
		return m_data;
	}

	foo_data* Klass::get_data() {
		return new foo_data();
	}

	std::string* Klass::get_string_ptr() {
		std::string *str_ptr = new std::string(get_string());
		return str_ptr;
	}

	std::shared_ptr<std::string> Klass::get_string_smart_ptr() {
		return std::shared_ptr<std::string>(get_string_ptr());// , delete_string);
	}

	string_wrapper Klass::get_wrapped_string()
	{
		return string_wrapper{ get_string() };
	}

	std::string Klass::get_string() {
		std::string some_local_string = "12345";
		some_local_string += "6789";
		str_operate(&some_local_string);
		return some_local_string;
	}

	void Klass::str_operate(std::string* str) {
		str->append("0");
	}

	void Klass::do_something_else( double f )
	{
		int intpart = static_cast<int>(f);
		m_data += intpart;
	}


//struct Klass2 : public virtual IKlass2, public Klass
//{
//	Klass2()
//		: m_data( 0 )
//	{
//		cerr << "Klass2 constructor\n";
//	}
//
//	~Klass2()
//	{
//		cerr << "Klass2 destructor\n";
//	}
//
//	void destroy()
//	{
//		delete this;
//	}
//
//	bool extension( int &p )
//	{
//		++p;
//		return false;
//	}
//
//	int do_stuff( int param )
//	{
//		return m_data * 2;
//	}
//
//	void do_something_else( double f )
//	{
//		int intpart = static_cast<int>(f);
//		m_data += intpart;
//	}
//protected:
//	int m_data;
//};

//extern "C"__declspec(dllexport) IKlass* __cdecl create_klass()
//{
//	return new Klass;
//}


BOOL APIENTRY DllMain( HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch ( ul_reason_for_call )
	{
	case DLL_PROCESS_ATTACH:
		MessageBox( 0, "Test", "From unmanaged dll", 0 );
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}