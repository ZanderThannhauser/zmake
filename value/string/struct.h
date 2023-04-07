
#include "../struct.h"

struct string_value
{
	struct value super;
	char* chars;
	unsigned len;
};

