
#include <assert.h>

#include <debug.h>

#include "zebu.h"
#include "recipe.h"
#include "include.h"
#include "iterative.h"
#include "assignment.h"
#include "statement.h"

void evaluate_statement(
	struct zebu_statement* statement,
	struct recipeset* all_recipes,
	struct recipeset* propagate_ftimes,
	struct database* database,
	struct dirfd* absolute_dirfd,
	struct dirfd* local_dirfd,
	struct scope* scope)
{
	ENTER;
	
	if (statement->recipe)
	{
		evaluate_recipe_statement(
			/* struct zebu_recipe* zrecipe: */ statement->recipe,
			/* struct recipeset* all_recipes: */ all_recipes,
			/* struct recipeset* propagate_ftimes: */ propagate_ftimes,
			/* struct database* database: */ database,
			/* struct dirfd* dirfd: */ absolute_dirfd,
			/* struct scope* scope: */ scope);
	}
	else if (statement->assignment)
	{
		evaluate_assignment_statement(statement->assignment, scope);
	}
	else if (statement->conditional)
	{
		TODO;
	}
	else if (statement->iterative)
	{
		evaluate_iterative_statement(
			statement->iterative,
			all_recipes, propagate_ftimes,
			database,
			absolute_dirfd, local_dirfd,
			scope);
	}
	else if (statement->include)
	{
		evaluate_include_statement(
			statement->include,
			all_recipes, propagate_ftimes,
			database,
			absolute_dirfd, local_dirfd,
			scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
}