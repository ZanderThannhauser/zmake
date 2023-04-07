
#include "../inheritance.h"

#include "inheritance.h"
#include "print.h"
#include "free.h"

struct value_inheritance list_value_inheritance = {
	.print = list_value_print,
	.free = free_list_value,
};

