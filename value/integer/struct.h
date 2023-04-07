
#include <gmp.h>

#include "../struct.h"

struct integer_value
{
	struct value super;
	
	mpz_t value;
};

