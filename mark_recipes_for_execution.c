
#include <debug.h>

#include <heap/new.h>
#include <heap/is_nonempty.h>
#include <heap/pop.h>
#include <heap/push.h>
#include <heap/free.h>

#include <recipeset/foreach.h>
#include <recipeset/len.h>

#include <recipe/struct.h>
#include <recipe/compare_scores.h>

#include "mark_recipes_for_execution.h"

unsigned execution_round_id = 0;

void mark_recipes_for_execution(
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
	
	execution_round_id++;
	
	while (heap_is_nonempty(ready))
	{
		struct recipe* recipe = heap_pop(ready);
		
		if (recipe->execution.round < execution_round_id)
		{
			dpvs(recipe->target);
			
			recipe->execution.round = execution_round_id;
			recipe->execution.waiting = recipeset_len(recipe->dep_on) + recipeset_len(recipe->odep_on);
			
			recipeset_foreach(recipe->dep_on, ({
				void callback(struct recipe* dependency) {
					heap_push(ready, dependency);
				}
				callback;
			}));
			
			recipeset_foreach(recipe->odep_on, ({
				void callback(struct recipe* dependency) {
					heap_push(ready, dependency);
				}
				callback;
			}));
		}
	}
	
	free_heap(ready);
	
	EXIT;
}












