
#include <assert.h>
#include <string.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_string_values(
	const struct value* a,
	const struct value* b)
{
	const struct string_value *A = (const struct string_value*) a;
	const struct string_value *B = (const struct string_value*) b;
	
	return strverscmp(A->chars, B->chars);
}

