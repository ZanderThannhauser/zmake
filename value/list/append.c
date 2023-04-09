
#include <debug.h>

#include <memory/srealloc.h>

#include <value/inc.h>

#include "struct.h"
#include "append.h"

void list_value_append(
	struct list_value* this,
	struct value* element)
{
	ENTER;
	
	if (this->len == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		this->elements = srealloc(this->elements, sizeof(*this->elements) * this->cap);
	}
	
	this->elements[this->len++] = inc_value(element);
	
	EXIT;
}

