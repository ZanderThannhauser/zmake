
#include <stdio.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void list_value_print(
	struct value* super)
{
	ENTER;
	
	struct list_value* this = (void*) super;
	
	putchar('[');
	
	for (unsigned i = 0, n = this->len; i < n; i++)
	{
		value_print(this->elements[i]);
		
		if (i + 1 < n)
			putchar(','), putchar(' ');
	}
	
	putchar(']');
	
	EXIT;
}

