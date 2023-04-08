
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include <value/struct.h>
#include <value/boolean/struct.h>
#include <value/free.h>

#include "evaluate/root.h"
#include "statement.h"
#include "conditional.h"

void evaluate_conditional_statement(
	struct zebu_conditional* conditional,
	struct recipeset* all_recipes,
	struct recipeset* propagate_ftimes,
	struct database* database,
	struct dirfd* absolute_dirfd,
	struct dirfd* local_dirfd,
	struct scope* scope)
{
	ENTER;
	
	struct value* gcond = evaluate_expression(conditional->conditional, scope);
	
	if (gcond->kind != vk_boolean)
	{
		TODO;
		exit(1);
	}
	
	struct boolean_value* cond = (void*) gcond;
	
	if (cond->value)
	{
		for (unsigned i = 0, n = conditional->truecase.n; i < n; i++)
		{
			struct zebu_statement* statement = conditional->truecase.data[i];
			
			evaluate_statement(
				statement,
				all_recipes, propagate_ftimes,
				database,
				absolute_dirfd, local_dirfd,
				scope);
		}
	}
	else
	{
		for (unsigned i = 0, n = conditional->falsecase.n; i < n; i++)
		{
			struct zebu_statement* statement = conditional->falsecase.data[i];
			
			evaluate_statement(
				statement,
				all_recipes, propagate_ftimes,
				database,
				absolute_dirfd, local_dirfd,
				scope);
		}
	}
	
	free_value(gcond);
	
	EXIT;
}













