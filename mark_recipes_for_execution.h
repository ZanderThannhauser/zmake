
struct recipeset;
struct heap;

extern unsigned execution_round_id;

void mark_recipes_for_execution(
	struct recipeset* start);
