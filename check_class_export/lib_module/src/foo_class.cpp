#include "foo_class.h"


#include "accessor.h"

unsigned int foo_data::get_cnt() {
	static unsigned int cnt = 0;
	return ++cnt;
}

foo_data::foo_data() {
	current_cnt = get_cnt();
	out << "foo_data ctor: " << current_cnt << "\n";
	complex_data = "1234567890";
}
foo_data::foo_data(const foo_data& other) {
	current_cnt = get_cnt();
	out << "foo_data copy ctor: " << other.current_cnt << " -> " << current_cnt << "\n";
}
foo_data& foo_data::operator=(const foo_data& other) {
	out << "foo_data op = : " << other.current_cnt << " -> " << current_cnt << "\n";
	current_cnt = other.current_cnt;

	return *this;
}
foo_data::~foo_data() {
	out << "foo_data ~dtor: " << current_cnt << "\n";
}




class foo_class::Factory {
public:
	Factory() {}
	foo_class_i* Build();

protected:
	virtual foo_class_i::data_type* CreateData() {
		foo_class_i::data_type* data = new foo_class_i::data_type();
		return data;
	}


  virtual std::unique_ptr<foo_class_i> HeapAlloc(const foo_class_i::data_type* data) {
	  return std::unique_ptr<foo_class_i>(new foo_class(data));
  }

private:
	DISALLOW_COPY_AND_ASSIGN(Factory);
};


foo_class_i* foo_class::Factory::Build() {
	const foo_class_i::data_type* created_ranges =
		reinterpret_cast<const foo_class_i::data_type*>(0xDEADBEEF);
	const foo_class_i::data_type* registered_ranges =
      reinterpret_cast<const foo_class_i::data_type*>(0xDEADBEEF);
	std::unique_ptr<foo_class_i> tentative_histogram;	

	created_ranges = CreateData();
	registered_ranges = accessor::register_data(created_ranges);
	tentative_histogram = HeapAlloc(registered_ranges);

	foo_class_i* result = accessor::register_class(tentative_histogram.release());

	return result;
}


foo_class_i* foo_class::factory_get() {
	return Factory().Build();
}

foo_class_i::foo_class_i() {
	out << "foo_class_I ctor \n";
}

foo_class_i::~foo_class_i() {
	out << "foo_class_I ~dtor \n";
}





foo_class::~foo_class()
{ 
	out << "foo_class ~dtor\n";
}

foo_class::foo_class(const data_type* data):data_(data) {
	out << "foo_class ctor: " << data->current_cnt << "\n";
}


