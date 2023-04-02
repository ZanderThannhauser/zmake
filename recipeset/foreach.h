
struct recipeset;
struct recipe;

void recipeset_foreach(
	const struct recipeset* this,
	void (*callback)(struct recipe* recipe));
