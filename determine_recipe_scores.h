
struct database;
struct heap;
struct recipeset;

void determine_recipe_scores(
	struct recipeset* all_recipes,
	struct heap* ready,
	struct database* database);
