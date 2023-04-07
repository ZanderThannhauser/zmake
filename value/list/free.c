
#include <stdlib.h>

#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_list_value(
	struct value* super)
{
	ENTER;
	
	struct list_value* this = (void*) super;
	
	for (unsigned i = 0, n = this->len; i < n; i++)
		free_value(this->elements[i]);
	
	free(this->elements);
	
	EXIT;
}

