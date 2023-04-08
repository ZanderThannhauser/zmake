
#include "../inheritance.h"

#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct value_inheritance integer_value_inheritance = {
	.compare = compare_integer_values,
	.print = integer_value_print,
	.free = free_integer_value,
};

