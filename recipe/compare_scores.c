
#include <string.h>

#include <debug.h>

#include "struct.h"
#include "compare_scores.h"

int compare_recipe_scores(
	const void* a,
	const void* b)
{
	const struct recipe* A = a, *B = b;
	
	if (A->ftimes.effective < B->ftimes.effective)
		return +1;
	else if (A->ftimes.effective > B->ftimes.effective)
		return -1;
	else if (A->ftimes.real < B->ftimes.real)
		return +1;
	else if (A->ftimes.real > B->ftimes.real)
		return -1;
	else
		return strverscmp(A->target, B->target);
}

