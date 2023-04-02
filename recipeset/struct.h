
struct recipeset
{
	struct avl_tree_t* tree;
	bool should_refcount_elements;
	unsigned n;
};
