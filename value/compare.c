
#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "compare.h"

int compare_values(
	const struct value* a,
	const struct value* b)
{
	int cmp;
	ENTER;
	
	cmp = 0
		?: a->kind - b->kind
		?: (a->inheritance->compare)(a, b);
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}

