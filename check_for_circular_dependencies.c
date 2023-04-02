
#include <debug.h>

#include <recipeset/foreach.h>

#include <recipe/struct.h>

#include "check_for_circular_dependencies.h"

void check_for_circular_dependencies(
	struct recipeset* all_recipes)
{
	ENTER;
	
	recipeset_foreach(all_recipes, ({
		void callback(struct recipe* recipe)
		{
			void helper(struct recipe* recipe)
			{
				if (recipe->circular.checked)
				{
					; // nothing to do
				}
				else if (recipe->circular.visited)
				{
					// "circaliar depenency!";
					TODO;
					exit(1);
				}
				else
				{
					recipe->circular.visited = true;
					
					recipeset_foreach(recipe->dep_on, helper);
					
					recipe->circular.visited = false;
					recipe->circular.checked = true;
				}
			}
			helper(recipe);
		}
		callback;
	}));
	
	EXIT;
}



