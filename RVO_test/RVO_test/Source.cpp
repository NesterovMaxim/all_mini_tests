#include <iostream>

struct C {
  C() {}
  C(const C&) { std::cout << "A copy was made.\n"; }
  C& operator=(C&) {
	  std::cout << "A = was made.\n"; return *this;
  }
};

C f() {
  auto c = C();
  return c;
}

int main() {
  std::cout << "Hello World!\n";
  //C obj = f();
  
  auto t = C();
  //C w; w = t;

  C q = t;

  std::getchar();
  return 0;
}