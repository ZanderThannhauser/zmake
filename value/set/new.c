
#include <debug.h>

#include <avl/alloc_tree.h>

#include "../new.h"
#include "../compare.h"
#include "../free.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct value* new_set_value()
{
	ENTER;
	
	struct set_value* this = (void*) new_value(
		vk_set,
		&set_value_inheritance,
		sizeof(*this));
	
	this->tree = avl_alloc_tree(
		(void*) compare_values,
		(void*) free_value);
	
	EXIT;
	return (struct value*) this;
}

