#include <iostream>

class base
{
public:
	virtual void f1() = 0;
};

class derived : public base
{
public:
	virtual void f2() = 0;	
};

class impl : public derived
{
public:
	virtual void f1()
	{
			std::cout << "derived::f1()\n";			
	}
	virtual void f2()
	{
			std::cout << "derived::f2()\n";			
	}
};

int main()
{
	base* inst = new impl();
	derived* inst_b = dynamic_cast<derived*>(inst);

	if (inst_b != nullptr)
		inst_b->f2();
	else
		std::cout <<"error\n";

	return 0;
}
