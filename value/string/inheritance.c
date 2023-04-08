
#include "../inheritance.h"

#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct value_inheritance string_value_inheritance = {
	.compare = compare_string_values,
	.print = string_value_print,
	.free = free_string_value,
};

