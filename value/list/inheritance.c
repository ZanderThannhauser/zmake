
#include "../inheritance.h"

#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct value_inheritance list_value_inheritance = {
	.compare = compare_list_values,
	.print = list_value_print,
	.free = free_list_value,
};

