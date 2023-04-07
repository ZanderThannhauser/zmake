
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_dirfds(
	const struct dirfd* A,
	const struct dirfd* B)
{
	if (A->dev < B->dev)
		return -1;
	else if (A->dev > B->dev)
		return +1;
	else if (A->ino < B->ino)
		return -1;
	else if (A->ino > B->ino)
		return +1;
	else
		return +0;
}

