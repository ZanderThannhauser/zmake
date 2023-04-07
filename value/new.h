
#include <stddef.h>

#include "kind.h"

struct value_inheritance;

struct value* new_value(
	enum value_kind kind,
	struct value_inheritance* inheritance,
	size_t alloc_size);
