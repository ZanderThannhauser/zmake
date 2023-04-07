
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct value* new_integer_value(
	mpz_t value)
{
	ENTER;
	
	struct integer_value* this = (void*) new_value(
		vk_integer,
		&integer_value_inheritance,
		sizeof(*this));
	
	mpz_init(this->value);
	mpz_set(this->value, value);
	
	EXIT;
	return (struct value*) this;
}

