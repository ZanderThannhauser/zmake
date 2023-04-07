
struct value;

struct value_inheritance
{
	void (*print)(struct value* super);
	void (*free)(struct value* super);
};

