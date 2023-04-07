
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <scope/assign.h>

#include <value/struct.h>
#include <value/free.h>
#include <value/list/struct.h>

#include "evaluate/root.h"
#include "statement.h"
#include "iterative.h"
#include "zebu.h"

void evaluate_iterative_statement(
	struct zebu_iterative* iterative,
	struct recipeset* all_recipes,
	struct recipeset* propagate_ftimes,
	struct database* database,
	struct dirfd* absolute_dirfd,
	struct dirfd* local_dirfd,
	struct scope* scope)
{
	ENTER;
	
	char* variable = (char*) iterative->variable->data;
	
	dpvs(variable);
	
	struct value* glist = evaluate_expression(iterative->list, scope);
	
	if (glist->kind != vk_list)
	{
		TODO;
		exit(1);
	}
	
	struct list_value* list = (void*) glist;
	
	for (unsigned i = 0, n = list->len; i < n; i++)
	{
		struct value* element = list->elements[i];
		
		scope_assign(scope, variable, element);
		
		for (unsigned j = 0, m = iterative->body.n; j < m; j++)
		{
			struct zebu_statement* statement = iterative->body.data[j];
			
			evaluate_statement(
				/* struct zebu_statement* */ statement,
				/* struct recipeset* */ all_recipes,
				/* struct recipeset* */ propagate_ftimes,
				/* struct database* */ database,
				/* struct dirfd* */ absolute_dirfd,
				/* struct dirfd* */ local_dirfd,
				/* struct scope* */ scope);
		}
	}
	
	free_value(glist);
	
	EXIT;
}


















