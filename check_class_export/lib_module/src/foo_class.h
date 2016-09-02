#pragma once

#include "common.h"

#include <memory>
#include <string>
#include <vector>

class FOO_EXPORT foo_data {
private:
	unsigned int get_cnt();
public:
	foo_data();
	foo_data(const foo_data& other);
	foo_data& operator=(const foo_data& other);
	~foo_data();
public:
	unsigned int current_cnt = 0;
	std::string complex_data;
};

class foo_class;

class FOO_EXPORT foo_class_i {

public:
	using data_type = foo_data;
	using data_uptr = std::unique_ptr<data_type>;
	using data_sptr = std::unique_ptr<data_type>;

public:
	foo_class_i();
	virtual ~foo_class_i();

	//return only unique_ptr on data (or raw pointer)
	//virtual data_uptr get_static_data() = 0;
	//virtual data_uptr get_dynamic_data() = 0;
	//virtual void get_data(std::vector<foo_data> *data) = 0;

private:
	const data_type dyn_data;

private:
	DISALLOW_COPY_AND_ASSIGN(foo_class_i);
};




class FOO_EXPORT foo_class : public foo_class_i {
public:
	~foo_class() override;

	static foo_class_i* factory_get();

	//it using only inside due foo_class_i interface not include any static
	//static void fill_the_data(data_type* data);
	//static void save_data(const data_type& p);
	//static void save_data(const data_sptr p);

	//return only unique_ptr on data (or raw pointer)
	//virtual data_uptr get_static_data() override;
	//virtual data_uptr get_dynamic_data() override;

protected:
	class Factory;
	foo_class(const data_type* data);

private:
	//virtual void get_data(std::vector<data_type> *data) override;

private:
	friend class accessor;

	// Does not own this object. Should get from accessor.
	const data_type* data_;

private:
	//static std::vector<data_type> data;
	//static std::vector<data_uptr> data_up;
//	static std::vector<data_sptr> data_sp;
private:
	DISALLOW_COPY_AND_ASSIGN(foo_class);
};
