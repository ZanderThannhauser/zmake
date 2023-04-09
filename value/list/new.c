
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct value* new_list_value()
{
	ENTER;
	
	struct list_value* this = (void*) new_value(
		vk_list,
		&list_value_inheritance,
		sizeof(*this));
	
	this->elements = NULL;
	this->len = 0;
	this->cap = 0;
	
	EXIT;
	return (struct value*) this;
}

