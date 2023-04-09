
struct set_value;

void set_value_foreach(
	struct set_value* this,
	void (*callback)(struct value*));
