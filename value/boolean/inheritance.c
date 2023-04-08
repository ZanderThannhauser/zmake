
#include "../inheritance.h"

#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct value_inheritance boolean_value_inheritance = {
	.compare = compare_boolean_values,
	.print = boolean_value_print,
	.free = free_boolean_value,
};

