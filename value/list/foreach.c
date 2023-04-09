
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void list_value_foreach(
	struct list_value* this,
	void (*callback)(struct value*))
{
	ENTER;
	
	for (unsigned i = 0, n = this->len; i < n; i++)
		callback(this->elements[i]);
	
	EXIT;
}

