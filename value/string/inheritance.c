
#include "../inheritance.h"

#include "inheritance.h"
#include "print.h"
#include "free.h"

struct value_inheritance string_value_inheritance = {
	.print = string_value_print,
	.free = free_string_value,
};

