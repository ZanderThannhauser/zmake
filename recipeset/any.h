
struct recipeset;
struct recipe;

bool recipeset_any(
	const struct recipeset* this,
	bool (*callback)(const struct recipe*));
