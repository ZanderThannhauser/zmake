
#include <assert.h>

#include <stdio.h>

#include <debug.h>

#include <avl/tree.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void set_value_print(
	struct value* super)
{
	ENTER;
	
	struct set_value* this = (void*) super;
	
	putchar('{');
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		TODO;
	}
	
	#if 0
	for (unsigned i = 0, n = this->len; i < n; i++)
	{
		value_print(this->elements[i]);
		
		if (i + 1 < n)
			putchar(','), putchar(' ');
	}
	#endif
	
	putchar('}');
	
	EXIT;
}

