
#include <assert.h>

#include <debug.h>

#include <cmdln/options/verbose.h>

#include <value/print.h>
#include <value/free.h>

#include <scope/assign.h>
#include <scope/lookup.h>

#include "evaluate/root.h"
#include "evaluate/additive.h"

#include "zebu.h"
#include "assignment.h"

void evaluate_assignment_statement(
	struct zebu_assignment* assignment,
	struct scope* scope)
{
	ENTER;
	
	TODO;
	#if 0
	const char* name = (char*) assignment->variable->data;
	
	if (assignment->eq)
	{
		struct value* value = evaluate_expression(assignment->expression, scope);
		
		scope_assign(scope, name, value);
		
		if (cmdln_verbose)
		{
			printf("%s = ", name), value_print(value), puts("");
		}
		
		free_value(value);
	}
	else if (assignment->addeq)
	{
		struct value* left = scope_lookup(scope, name);
		
		struct value* right = evaluate_expression(assignment->expression, scope);
		
		struct value* value = perform_add(left, right);
		
		scope_assign(scope, name, value);
		
		if (cmdln_verbose)
		{
			printf("%s = ", name), value_print(value), puts("");
		}
		
		free_value(left), free_value(right);
		
		free_value(value);
	}
	else
	{
		TODO;
	}
	#endif
	
	EXIT;
}















