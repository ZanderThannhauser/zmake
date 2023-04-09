
#include "../struct.h"

struct set_value
{
	struct value super;
	
	struct avl_tree_t* tree;
	
	unsigned len;
};

