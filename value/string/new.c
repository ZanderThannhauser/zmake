
#include <string.h>

#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct value* new_string_value(
	const char* chars,
	unsigned len)
{
	ENTER;
	
	struct string_value* this = (void*) new_value(
		vk_string,
		&string_value_inheritance,
		sizeof(*this));
	
	this->chars = strndup(chars, len);
	this->len = len;
	
	EXIT;
	return (struct value*) this;
}

