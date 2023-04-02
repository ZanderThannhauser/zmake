
struct recipeset;
struct heap;

void mark_recipes_for_execution(
	struct recipeset* all_recipes,
	struct heap* ready);
