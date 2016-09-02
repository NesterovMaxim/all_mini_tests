#include "accessor.h"

// static
std::unique_ptr<accessor::Histograms> accessor::histograms_;
// static
std::unique_ptr<accessor::RangesMap> accessor::ranges_;

void accessor::Initialize() {
	static std::unique_ptr<accessor> g_statistics_recorder_(new accessor());
	if ( histograms_ == nullptr )
		g_statistics_recorder_.reset(new accessor());
}

void accessor::Reset() {
	histograms_.reset();
	ranges_.reset();
}

accessor::accessor() {
	histograms_.reset(new Histograms);
	ranges_.reset(new RangesMap);
}

accessor::~accessor() {
	Reset();
}



const foo_class_i::data_type* accessor::register_data(const foo_class_i::data_type* ranges){
	if ( !ranges_ ) {
		return ranges;
	}

	(*ranges_)[ranges->current_cnt] = ranges;

	return ranges;
}

foo_class_i* accessor::register_class(foo_class_i* obj) {
	if ( !histograms_ )
		return obj;

	histograms_->push_back(obj);

	return obj;
}