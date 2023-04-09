
struct list_value;

void list_value_foreach(
	struct list_value* this,
	void (*callback)(struct value*));
