#include <iostream>

struct TemporaryObject
{
    TemporaryObject()
        :
    mActive(true)
    { 
        std::cout << "TemporaryObject::ctor mActive = " << mActive << ", this = " << (void*)this << std::endl;
    }

    TemporaryObject(const TemporaryObject& obj)
        :
    mActive(obj.mActive)
    { 
        obj.mActive = false;
        std::cout << "TemporaryObject::copy_ctor mActive = " << mActive << ", this = " << (void*)this << std::endl;
    }

    ~TemporaryObject()
    {
        std::cout << "TemporaryObject::dtor mActive = " << mActive << ", this = " << (void*)this << std::endl;
        // assert(!mActive);
    }

    mutable bool mActive;
};

struct MyObject
{
    MyObject(const TemporaryObject& obj)
    {
        std::cout << "MyObject::ctor obj.mActive = " << obj.mActive << ", &obj = " << (void*)(&obj) << std::endl;
        obj.mActive = false;
    }
};

TemporaryObject SimpleFunction()
{
    TemporaryObject obj;

    // Do stuff

    return obj;
}

int main()
{
    MyObject obj = SimpleFunction();
}