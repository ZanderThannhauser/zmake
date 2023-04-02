
#include <debug.h>

#include "struct.h"
#include "compare_targets.h"

int compare_recipe_targets(
	const void* a,
	const void* b)
{
	const struct recipe* A = a, *B = b;
	
	return strverscmp(A->target, B->target);
}

