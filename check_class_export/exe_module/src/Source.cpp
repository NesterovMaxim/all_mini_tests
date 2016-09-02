#include <stdio.h>

#include "../../lib_module/src/foo_class.h"

int main() {
	const auto obj = foo_class::factory_get();

	delete obj;

	return 0;
}