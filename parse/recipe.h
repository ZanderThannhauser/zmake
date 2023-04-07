
struct recipeset;
struct database;
struct dirfd;
struct zebu_recipe;
struct scope;

void evaluate_recipe_statement(
	struct zebu_recipe* zrecipe,
	struct recipeset* all_recipes,
	struct recipeset* propagate_ftimes,
	struct database* database,
	struct dirfd* dirfd,
	struct scope* scope);
	
