#include <iostream>
#include <functional>
using namespace std;

		struct scope_guard {
			using op_t = std::function<void()>;
			scope_guard(const op_t op) :m_op(op) {}
			~scope_guard() {m_op();}

		private:
			const op_t m_op;
		};

	struct checker{
		checker(unsigned i){cout << "created: "<<i<<"\n"; d = i;}
		~checker(){cout << "deleted: "<<d<<"\n"; d = 666-d;}
		
		unsigned d;
	};

	struct bar {
		void foo() {
			checker ch(1);
			checker ch1(2);
			const auto tester = []() {cout << "param!\n" << endl; };
			scope_guard g(tester);
		}

		unsigned 
	};


int main() {
	foo();
	
	return 0;
}