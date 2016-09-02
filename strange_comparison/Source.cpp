#include <iostream>

class id_t {
	typedef	int	value_type;
public:
	id_t() {
	}
	id_t(const value_type val) {

	}

	//operator bool() const {
	//	return true;
	//}

	bool operator == (const id_t &o) const {
		return o.value == value;
	}

	void set(value_type val) {
		value = val;
	}
private:
	value_type	value;
};

int main() {
	id_t id;
	id.set(123);
	if ( id == 1 ) {
		std::cout << "equal!\n";
	}
	else {
		std::cout << "WTF\n";
	}
}