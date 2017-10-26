//clang 3.8.0

#include <iostream>
#include <functional>

using ft = std::function<void(int)>;

void p(const char* m, int i){
    std::cout << m << ":" << i << std::endl;
}

int i;
class test{
    int j;
public:
    test(){j = ++i; p("ctor", j);}
    ~test(){p("dtor", j);}
    
    test(const test& t){j = t.j*10; p("copy ctor", j);}
    test(test&& t){j = t.j*100; p("move ctor", j);}
    
    void operator()(int i){
        std::cout << i << std::endl;
    }
};

int main()
{
    test o;
    ft f;    
   
    //f = [&o](int i){o(i);};
    f = o;
    f(1);
    
    std::cout << "Hello, world!\n";
    return 0;
}
/*
ctor:1
copy ctor:10
move ctor:1000
dtor:10
1
Hello, world!
dtor:1000
dtor:1
 */
