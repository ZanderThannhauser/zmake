
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <scope/assign.h>

#include <value/struct.h>
#include <value/free.h>
#include <value/list/foreach.h>
#include <value/set/foreach.h>

#include "evaluate/root.h"
#include "statements.h"
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
	
	void foreach(struct value* element)
	{
		ENTER;
		
		scope_assign(scope, variable, element);
		
		evaluate_statements(
			/* struct zebu_statement* */ iterative->body,
			/* struct recipeset* */ all_recipes,
			/* struct recipeset* */ propagate_ftimes,
			/* struct database* */ database,
			/* struct dirfd* */ absolute_dirfd,
			/* struct dirfd* */ local_dirfd,
			/* struct scope* */ scope);
		
		EXIT;
	}
	
	struct value* value = evaluate_expression(iterative->list, scope);
	
	switch (value->kind)
	{
		case vk_list:
			list_value_foreach((struct list_value*) value, foreach);
			break;
		
		case vk_set:
			set_value_foreach((struct set_value*) value, foreach);
			break;
		
		default:
			TODO;
			exit(1);
			break;
	}
	
	
	free_value(value);
	
	EXIT;
}


















