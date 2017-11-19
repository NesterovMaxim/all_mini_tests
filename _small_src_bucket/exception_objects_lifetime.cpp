//clang 3.8.0

#include <iostream>
#include <string>

struct tst{
    explicit tst(char const *const p){
        std::cout << "explicit tst ctor\n";
    }
    tst(char const *const p, int){
        std::cout << "tst ctor\n";
    }
};

struct dtst : public tst{
    explicit dtst(const std::string& p):tst(p.c_str()){
        std::cout << "explicit dtst string ctor\n";
    }
    explicit dtst(const char* p):tst(p){
        std::cout << "explicit dtst char* ctor\n";
    }
};

struct ddtst : public dtst{
    ddtst(const std::string& p):dtst(p){
        std::cout << "ddtst string ctor\n";
    }
};

int main()
{
    ddtst t("1");
    std::cout << "END\n";
}
