
#include <string.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_scope_nodes(const void* a, const void* b)
{
	const struct scope_node *A = a, *B = b;
	return strverscmp(A->name, B->name);
}

