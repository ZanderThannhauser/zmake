
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <recipeset/foreach.h>

#include <recipe/struct.h>

#include "check_for_circular_dependencies.h"

static unsigned round_id = 1;

void check_for_circular_dependencies(
	struct recipeset* all_recipes)
{
	ENTER;
	
	recipeset_foreach(all_recipes, ({
		void callback(struct recipe* recipe)
		{
			void helper(struct recipe* recipe)
			{
				if (recipe->circular.checked == round_id)
				{
					; // nothing to do
				}
				else if (recipe->circular.visited == round_id)
				{
					// "circular depenency!";
					TODO;
					exit(1);
				}
				else
				{
					recipe->circular.visited = true;
					
					recipeset_foreach(recipe->dep_on, helper);
					
					recipe->circular.visited = false;
					recipe->circular.checked = round_id;
				}
			}
			helper(recipe);
		}
		callback;
	}));
	
	round_id++;
	
	EXIT;
}



