
#include <stdbool.h>

#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct value* new_boolean_value(bool value)
{
	ENTER;
	
	struct boolean_value* this = (void*) new_value(
		vk_boolean,
		&boolean_value_inheritance,
		sizeof(*this));
	
	this->value = value;
	
	EXIT;
	return (struct value*) this;
}

