
#include "../inheritance.h"

#include "inheritance.h"
#include "print.h"
#include "free.h"

struct value_inheritance integer_value_inheritance = {
	.print = integer_value_print,
	.free = free_integer_value,
};

