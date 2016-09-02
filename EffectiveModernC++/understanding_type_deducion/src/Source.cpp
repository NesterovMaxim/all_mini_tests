#include <iostream>
#include <boost\type_index.hpp>

using boost::typeindex::type_id_with_cvr;

#define BUILD_FUNC_TEMPLATE(name, T_type) \
	template<typename T> \
	void name(T_type val){ \
		std::cout << "\tparam = " << type_id_with_cvr<decltype(val)>().pretty_name() << std::endl; \
		std::cout << "\tT     = " << type_id_with_cvr<T>().pretty_name() << std::endl; \
	}

#define CALL_FUNC(func_name, param) \
	std::cout << "\t->pass= " << #param << "\ttype: " << type_id_with_cvr<decltype(param)>().pretty_name() <<"\n";\
	func_name(param)

#define CALL_FUNC_TEMPLATE(func_name) \
	std::cout << #func_name << std::endl; \
	CALL_FUNC(func_name, 7);\
	CALL_FUNC(func_name, x); \
	CALL_FUNC(func_name, cx); \
	CALL_FUNC(func_name, rx); \
	std::cout << "====================================\n"

#define CALL_FUNC_TEMPLATE_WITHOUT_rvalue(func_name) \
	std::cout << #func_name << std::endl; \
	CALL_FUNC(func_name, x); \
	CALL_FUNC(func_name, cx); \
	CALL_FUNC(func_name, rx); \
	std::cout << "====================================\n"


BUILD_FUNC_TEMPLATE(just_T, T)
BUILD_FUNC_TEMPLATE(const_T, const T)
BUILD_FUNC_TEMPLATE(ref_T, T&)
BUILD_FUNC_TEMPLATE(const_ref_T, const T&)
BUILD_FUNC_TEMPLATE(uref_T, T&&)

//BUILD_FUNC_TEMPLATE(pass_array, int[])

template<typename T>
void pass_array(T& val) {
		std::cout << "\tparam = " << type_id_with_cvr<decltype(val)>().pretty_name() << std::endl;
		std::cout << "\tT     = " << type_id_with_cvr<T>().pretty_name() << std::endl;
}

int main() {
	int x = 27;
	const int cx = x;
	const int& rx = x;

	CALL_FUNC_TEMPLATE(just_T);
	CALL_FUNC_TEMPLATE(const_T);
	CALL_FUNC_TEMPLATE_WITHOUT_rvalue(ref_T);
	CALL_FUNC_TEMPLATE(const_ref_T);

	CALL_FUNC_TEMPLATE(uref_T);

	int array[5];
	CALL_FUNC(pass_array, array);

	//CALL_FUNC_TEMPLATE(const_uref_T); //should move parameter

	std::getchar();
	return 0;
}
