#pragma once

#include <memory>
#include <string>

#if defined(FOO_IMPLEMENTATION)
#define FOO_EXPORT __declspec(dllexport)
#else
#define FOO_EXPORT __declspec(dllimport)
#endif  // defined(BASE_IMPLEMENTATION)

class foo_data {
private:
	unsigned int get_cnt();
public:
	foo_data();
	foo_data(const foo_data& other);
	foo_data& operator=(const foo_data& other);
	virtual ~foo_data();
public:
	unsigned int current_cnt = 0;
	std::string complex_data;
};

class FOO_EXPORT string_wrapper {
public:
	std::string data;
};

struct TestClass_i {
	virtual bool get_string(std::shared_ptr<std::string>& smart_ptr) = 0;
};

struct TestClass: public TestClass_i {
	virtual bool get_string(std::shared_ptr<std::string>& smart_ptr) override;
};


extern "C" __declspec(dllexport)
TestClass_i* create_test_class();

struct FOO_EXPORT IKlass 
{
	virtual ~IKlass() {};
	virtual void destroy() = 0;
	virtual int do_stuff( int param ) = 0;	
	virtual foo_data* get_data() = 0;
	virtual std::string get_string() = 0;
	virtual string_wrapper get_wrapped_string() = 0;
	virtual std::string* get_string_ptr() = 0;
	virtual std::shared_ptr<std::string> get_string_smart_ptr() = 0;
	virtual void do_something_else( double f ) = 0;
};

struct FOO_EXPORT Klass : public virtual IKlass {
	static IKlass* create();
	Klass();
	virtual ~Klass();
	virtual void destroy();
	virtual int do_stuff(int param);
	virtual foo_data* get_data();
	virtual std::string get_string();
	virtual string_wrapper get_wrapped_string();
	virtual std::string* get_string_ptr();
	virtual std::shared_ptr<std::string> get_string_smart_ptr();
	virtual void do_something_else(double f);
private:
	void str_operate(std::string* str);
protected:
	int m_data;
};
//struct IKlass2 : public virtual IKlass
//{
//	virtual bool extension( int &p ) = 0;	
//};