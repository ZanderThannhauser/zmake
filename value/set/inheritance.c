
#include "../inheritance.h"

#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct value_inheritance set_value_inheritance = {
	.compare = compare_set_values,
	.print = set_value_print,
	.free = free_set_value,
};

