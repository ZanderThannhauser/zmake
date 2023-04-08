
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_integer_values(
	const struct value* a,
	const struct value* b)
{
	ENTER;
	
	const struct integer_value *A = (const struct integer_value *) a;
	const struct integer_value *B = (const struct integer_value *) b;
	
	int cmp = mpz_cmp(A->value, B->value);
	
	EXIT;
	return cmp;
}

