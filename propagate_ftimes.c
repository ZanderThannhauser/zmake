
#include <debug.h>

#include <heap/new.h>
#include <heap/push.h>
#include <heap/pop.h>
#include <heap/is_nonempty.h>
#include <heap/free.h>

#include <recipe/struct.h>
#include <recipe/compare_scores.h>

#include <recipeset/foreach.h>

#include "propagate_ftimes.h"

void propagate_ftimes(
	struct recipeset* start)
{
	ENTER;
	
	struct heap* ready = new_heap(compare_recipe_scores);
	
	recipeset_foreach(start, ({
		void callback(struct recipe* recipe) {
			heap_push(ready, recipe);
		}
		callback;
	}));
	
	while (heap_is_nonempty(ready))
	{
		struct recipe* recipe = heap_pop(ready);
		
		dpvs(recipe->target);
		
		recipeset_foreach(recipe->dep_on, ({
			void callback(struct recipe* dependency)
			{
				if (recipe->ftimes.effective > dependency->ftimes.effective)
				{
					dependency->ftimes.effective = recipe->ftimes.effective;
					heap_push(ready, dependency);
				}
			}
			callback;
		}));
	}
	
	free_heap(ready);
	
	EXIT;
}








