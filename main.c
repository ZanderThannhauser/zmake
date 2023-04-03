
#include <stdio.h>

#include <debug.h>

#include <cmdln/process.h>
#include <cmdln/usage.h>
#include <cmdln/options/help.h>
#include <cmdln/options/makefiles.h>
#include <cmdln/options/print_dependency_tree.h>

#include <recipeset/new.h>

#include <recipe/compare_scores.h>
#include <heap/new.h>

#include <dirfd/new.h>
#include <dirfd/free.h>

#include <parse/parse.h>

#include <recipeset/lookup.h>
#include <heap/push.h>

#include <print_dependency_tree.h>

#include <mark_recipes_for_execution.h>

#include <check_for_circular_dependencies.h>

#include <database/new.h>
#include <database/cleanup.h>

#include <determine_recipe_scores.h>

#include <run_make_loop.h>

#include <heap/free.h>

#include <database/free.h>
#include <recipeset/free.h>
#include <cmdln/free.h>

int main(int argc, char* const* argv)
{
	ENTER;
	
	cmdln_process(argc, argv);
	
	if (cmdln_help)
	{
		puts(cmdln_usage_message);
	}
	else
	{
		TODO;
		#if 0
		struct database* database = new_database();
		
		database_cleanup(database);
		
		determine_recipe_scores(all_recipes, ready, database);
		#endif
		
		TODO;
		// struct recipeset* all_recipes = new_recipeset(true);
		
		TODO;
		#if 0
		struct heap* ready = new_heap(compare_recipe_scores);
		
		for (int i = 0, n = cmdln_makefiles.n; i < n; i++)
		{
			struct cmdln_makefile_bundle* bundle = &cmdln_makefiles.data[i];
			
			struct dirfd* dirfd = new_dirfd(bundle->chdir);
			
			struct scope* scope = new_scope();
			
			for (int j = 0, m = bundle->makefiles.n; j < m; j++)
			{
				const char* makefile = bundle->makefiles.data[j];
				
				parse(all_recipes, dirfd, scope, makefile);
			}
			
			for (int j = 0, m = bundle->targets.n; j < m; j++)
			{
				const char* target = bundle->targets.data[j];
				
				dpvs(target);
				
				struct recipe* recipe = recipeset_lookup(all_recipes, target, dirfd);
				
				heap_push(ready, recipe);
			}
			
			free_scope(scope);
			
			free_dirfd(dirfd);
		}
		#endif
		
		TODO;
		// mark_recipes_for_execution(ready);
		
		TODO;
		#if 0
		if (cmdln_print_dependency_tree)
		{
			print_dependency_tree(all_recipes);
		}
		else
		{
			check_for_circular_dependencies(all_recipes);
			
			run_make_loop(all_recipes, ready, database);
		}
		
		free_database(database);
		
		free_recipeset(all_recipes);
		
		free_heap(ready);
		#endif
	}
	
	cmdln_free();
	
	EXIT;
	return 0;
}
























