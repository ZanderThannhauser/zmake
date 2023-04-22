
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <fcntl.h>

#include <debug.h>

#include <cmdln/process.h>
#include <cmdln/usage.h>
#include <cmdln/options/help.h>
#include <cmdln/options/makefiles.h>
#include <cmdln/options/print_dependency_tree.h>
#include <cmdln/free.h>

#include <database/new.h>
#include <database/free.h>

#include <dirfd/new.h>
#include <dirfd/free.h>

#include <parse/parse.h>

#include <recipe/compare_scores.h>

#include <recipeset/new.h>
#include <recipeset/lookup.h>
#include <recipeset/add.h>
#include <recipeset/free.h>

#include <scope/new.h>
#include <scope/assign_builtins.h>
#include <scope/free.h>

#include <path/new.h>
#include <path/resolve.h>
#include <path/free.h>

#include <mark_recipes_for_execution.h>

#include <print_dependency_tree.h>

#include <check_for_circular_dependencies.h>

#include <run_make_loop.h>

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
		struct database* database = new_database();
		
		struct recipeset* all_recipes = new_recipeset(true);
		
		struct recipeset* targets = new_recipeset(false);
		
		struct path* root_path = new_root_path();
		
		char cwd[PATH_MAX];
		if (!getcwd(cwd, PATH_MAX))
		{
			TODO;
			exit(1);
		}
		
		dpvs(cwd);
		
		struct path* cwd_path = resolve_path(cwd, root_path, root_path);
		
		TODO;
		#if 0
		for (int i = 0, n = cmdln_makefiles.n; i < n; i++)
		{
			struct cmdln_makefile_bundle* bundle = &cmdln_makefiles.data[i];
			
			struct dirfd* dirfd = new_dirfd(AT_FDCWD, bundle->chdir);
			
			struct scope* scope = new_scope();
			
			scope_assign_builtins(scope);
			
			for (int j = 0, m = bundle->makefiles.n; j < m; j++)
			{
				const char* makefile = bundle->makefiles.data[j];
				
				parse(all_recipes, database, dirfd, scope, makefile);
			}
			
			for (int j = 0, m = bundle->targets.n; j < m; j++)
			{
				const char* target = bundle->targets.data[j];
				
				dpvs(target);
				
				struct recipe* recipe = recipeset_lookup(all_recipes, target, dirfd);
				
				if (!recipe)
				{
					TODO;
					exit(1);
				}
				
				recipeset_add(targets, recipe);
			}
			
			free_scope(scope);
			
			free_dirfd(dirfd);
		}
		
		mark_recipes_for_execution(targets);
		
		if (cmdln_print_dependency_tree)
		{
			print_dependency_tree(all_recipes);
		}
		else
		{
			check_for_circular_dependencies(all_recipes);
			
			run_make_loop(all_recipes, database);
		}
		
		free_recipeset(all_recipes);
		
		free_recipeset(targets);
		
		free_database(database);
		#endif
	}
	
	cmdln_free();
	
	EXIT;
	return 0;
}
























