
struct value;

struct value_inheritance
{
	int (*compare)(const struct value* a, const struct value* b);
	
	void (*print)(struct value* super);
	
	void (*free)(struct value* super);
};

