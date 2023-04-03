
#include <math.h>

#include <debug.h>

#include <recipeset/foreach.h>

#include <database/read_tests.h>

#include <recipe/struct.h>

#include <heap/push.h>
#include <heap/is_nonempty.h>
#include <heap/pop.h>

#include "determine_recipe_scores.h"

void determine_recipe_scores(
	struct recipeset* all_recipes,
	struct heap* ready,
	struct database* database)
{
	ENTER;
	
	database_read_tests(database, all_recipes);
	
	recipeset_foreach(all_recipes, ({
		void callback(struct recipe* recipe)
		{
			double score = INFINITY;
			
			if (recipe->scores.count)
				score = (double) recipe->scores.total / recipe->scores.count;
			
			recipe->scores.real = score;
			recipe->scores.effective = score;
			
			dpv(recipe->scores.effective);
			
			heap_push(ready, recipe);
		}
		callback;
	}));
	
	while (heap_is_nonempty(ready))
	{
		struct recipe* recipe = heap_pop(ready);
		
		recipeset_foreach(recipe->dep_on, ({
			void callback(struct recipe* dependency)
			{
				if (recipe->scores.effective < dependency->scores.effective)
				{
					dependency->scores.effective = recipe->scores.effective;
					heap_push(ready, dependency);
				}
			}
			callback;
		}));
	}
	
	EXIT;
}



















