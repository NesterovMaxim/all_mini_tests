#pragma once

#include "common.h"
#include "foo_class.h"

#include <map>

class FOO_EXPORT accessor {
public:
  typedef std::vector<foo_class_i*> Histograms;

public:
  static void Initialize();
	~accessor();

	static const foo_class_i::data_type* register_data(const foo_class_i::data_type* ranges);
	static foo_class_i* register_class(foo_class_i* obj);

private:
	// We keep all |bucket_ranges_| in a map, from checksum to a list of
	// |bucket_ranges_|.  Checksum is calculated from the |ranges_| in
	// |bucket_ranges_|.
	typedef std::map<uint32_t, const foo_class_i::data_type*> RangesMap;

	// The constructor just initializes static members. Usually client code should
	// use Initialize to do this. But in test code, you can friend this class and
	// call the constructor to get a clean StatisticsRecorder.
	accessor();

	static void Reset();

	static std::unique_ptr<Histograms> histograms_;
	static std::unique_ptr<RangesMap> ranges_;

private:
	DISALLOW_COPY_AND_ASSIGN(accessor);
};