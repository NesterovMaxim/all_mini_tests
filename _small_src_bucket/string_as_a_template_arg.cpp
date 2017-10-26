
struct F {
  static constexpr const char conststr[]= "some constr stru";
};

template <const char* histogram>
void foo() {
	UMA_HISTOGRAM_COUNTS_1000(histogram, 0);
}

void bar() {
	foo<F::conststr>();
}
