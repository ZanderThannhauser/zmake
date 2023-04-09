
#include "../struct.h"

struct list_value
{
	struct value super;
	
	struct value** elements;
	
	unsigned len, cap;
};

