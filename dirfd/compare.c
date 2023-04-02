
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_dirfds(
	const struct dirfd* A,
	const struct dirfd* B)
{
	if (A->st_dev < B->st_dev)
		return -1;
	else if (A->st_dev > B->st_dev)
		return +1;
	else if (A->st_ino < B->st_ino)
		return -1;
	else if (A->st_ino > B->st_ino)
		return +1;
	else
		return +0;
}

