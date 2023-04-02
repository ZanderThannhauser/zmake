
#include <string.h>

#include <debug.h>

#include <dirfd/compare.h>

#include "struct.h"
#include "compare_targets.h"

int compare_recipe_targets(
	const void* a,
	const void* b)
{
	const struct recipe* A = a, *B = b;
	
	int cmp = 0
		?: strverscmp(A->target, B->target)
		?: compare_dirfds(A->dirfd, B->dirfd);
	
	return cmp;
}

