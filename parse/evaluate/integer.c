
#include <stdlib.h>
#include <assert.h>
#include <gmp.h>

#include <debug.h>

#include <parse/zebu.h>

#include <value/integer/new.h>

#include "integer.h"

struct value* evaluate_integer_expression(
	struct zebu_token* token)
{
	ENTER;
	
	dpvs((char*) token->data);
	
	mpz_t mpz;
	
	if (mpz_init_set_str(mpz, (char*) token->data, 10) < 0)
	{
		TODO;
		exit(1);
	}
	
	struct value* result = new_integer_value(mpz);
	
	mpz_clear(mpz);
	
	EXIT;
	return result;
}

