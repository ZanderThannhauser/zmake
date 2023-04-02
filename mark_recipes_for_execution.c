
#include <debug.h>

#include <cmdln/options/targets.h>

#include <recipeset/new.h>
#include <recipeset/add.h>
#include <recipeset/lookup.h>
#include <recipeset/free.h>
#include <recipeset/foreach.h>

#include <heap/push.h>
#include <heap/is_nonempty.h>
#include <heap/pop.h>

#include <recipe/struct.h>

#include "mark_recipes_for_execution.h"

void mark_recipes_for_execution(
	struct recipeset* all_recipes,
	struct heap* ready)
{
	ENTER;
	
	struct recipeset* queued = new_recipeset(false);
	
	if (cmdln_targets.n)
	{
		for (unsigned i = 0, n = cmdln_targets.n; i < n; i++)
		{
			const char* target = cmdln_targets.data[i];
			
			dpvs(target);
			
			struct recipe* recipe = recipeset_lookup(all_recipes, target);
			
			if (!recipe)
			{
				fprintf(stderr, "%s: command-line invocation refered to "
					"target '%s' that could not be found in makefile!\n",
					argv0, target);
				exit(e_bad_cmdline_args);
			}
			
			if (recipeset_add(queued, recipe))
				heap_push(ready, recipe);
		}
	}
	else
	{
		struct recipe* recipe = recipeset_lookup(all_recipes, "default");
		
		if (recipe)
		{
			if (recipeset_add(queued, recipe))
				heap_push(ready, recipe);
		}
		else
		{
			// "no target given on command line, and no "default" target in makefile"
			TODO;
			exit(1);
		}
	}
	
	while (heap_is_nonempty(ready))
	{
		struct recipe* recipe = heap_pop(ready);
		
		recipe->execution.marked = true;
		
		recipeset_foreach(recipe->dep_on, ({
			void callback(struct recipe* dependencies)
			{
				if (recipeset_add(queued, dependencies))
					heap_push(ready, dependencies);
			}
			callback;
		}));
	}
	
	free_recipeset(queued);
	
	EXIT;
}









