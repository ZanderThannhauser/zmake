
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <cmdln/options/verbose.h>

#include <parse/zebu.h>

#include <value/struct.h>
#include <value/inc.h>
#include <value/free.h>
#include <value/print.h>

#include <scope/lookup.h>
#include <scope/assign.h>

#include "evaluate/additive.h"
#include "evaluate/root.h"

#include "assignments.h"

void evaluate_assignments_statement(
	struct zebu_assignments* assignments,
	struct scope* scope)
{
	ENTER;
	
	for (unsigned i = 0, n = assignments->assignments.n; i < n; i++)
	{
		struct zebu_assignment* assignment = assignments->assignments.data[i];

		const char* name = (char*) assignment->variable->data;

		struct zebu_assignment_operator* op = assignment->op;

		struct value* right = evaluate_expression(assignment->expression, scope);

		if (op->eq)
		{
			scope_assign(scope, name, right);
			
			if (cmdln_verbose)
			{
				printf("%s = ", name), value_print(right), puts("");
			}
		}
		else if (op->opteq)
		{
			struct value* left = scope_lookup(scope, name);
			
			if (!left)
			{
				scope_assign(scope, name, right);
				
				if (cmdln_verbose)
				{
					printf("%s = ", name), value_print(right), puts("");
				}
			}
			
			free_value(left);
		}
		else if (op->addeq)
		{
			struct value* left = scope_lookup(scope, name);
			
			if (!left)
			{
				TODO;
				exit(1);
			}
			
			perform_addeq(left, right);
			
			free_value(left);
		}
		else
		{
			TODO;
		}
		
		free_value(right);
	}
}













