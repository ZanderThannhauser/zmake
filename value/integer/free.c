
#include <gmp.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_integer_value(
	struct value* super)
{
	ENTER;
	
	struct integer_value* this = (void*) super;
	
	mpz_clear(this->value);
	
	EXIT;
}

