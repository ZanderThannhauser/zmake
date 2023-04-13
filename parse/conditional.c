
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <parse/zebu.h>

#include <value/struct.h>
#include <value/boolean/struct.h>
#include <value/free.h>

#include "evaluate/root.h"
#include "statements.h"
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
	
	bool found = false;
	for (unsigned i = 0, n = conditional->conditionals.n; !found && i < n; i++)
	{
		struct value* gcond = evaluate_expression(conditional->conditionals.data[i], scope);
		
		if (gcond->kind != vk_boolean)
		{
			TODO;
			exit(1);
		}
		
		struct boolean_value* cond = (void*) gcond;
		
		if (cond->value)
		{
			evaluate_statements(
				conditional->cases.data[i],
				all_recipes, propagate_ftimes,
				database,
				absolute_dirfd, local_dirfd,
				scope);
			found = true;
		}
		
		free_value(gcond);
	}
	
	if (!found && conditional->fallback)
	{
		evaluate_statements(
			conditional->fallback,
			all_recipes, propagate_ftimes,
			database,
			absolute_dirfd, local_dirfd,
			scope);
	}
	
	EXIT;
}













