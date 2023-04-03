
#include <debug.h>

#include <heap/is_nonempty.h>
#include <heap/pop.h>
#include <heap/push.h>

#include <recipeset/foreach.h>

#include <recipe/struct.h>

#include "mark_recipes_for_execution.h"

void mark_recipes_for_execution(
	struct heap* ready)
{
	ENTER;
	
	// global round id, increments to invaildate previous execution markings
	
	
		// mark_recipes_for_execution(recipes):
			// global round = 0;
			// round++;
			// for recipe in recipes:
				// recipe.execution = round;
				// ready.add(recipe);
			// while len(ready):
				// recipe = ready.pop();
				// recipe.execution = round;
				// for dep in recipe.dep_on:
					// ready.push(dep);
		
	TODO;
	#if 0
	while (heap_is_nonempty(ready))
	{
		struct recipe* recipe = heap_pop(ready);
		
		if (!recipe->execution.marked)
		{
			recipe->execution.marked = true;
			
			recipeset_foreach(recipe->dep_on, ({
				void callback(struct recipe* dependency)
				{
					heap_push(ready, dependency);
				}
				callback;
			}));
		}
	}
	#endif
	
	EXIT;
}









