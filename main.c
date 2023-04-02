
#include <stdio.h>

#include <debug.h>

#include <cmdln/process.h>
#include <cmdln/usage.h>
#include <cmdln/options/directory.h>
#include <cmdln/options/help.h>
#include <cmdln/options/makefile.h>
#include <cmdln/options/print_dependency_tree.h>
#include <cmdln/free.h>

#include <parse/parse.h>

#include <print_dependency_tree.h>

#include <check_for_circular_dependencies.h>

#include <database/new.h>
#include <database/cleanup.h>

#include <recipe/compare_scores.h>
#include <heap/new.h>

#include <determine_recipe_scores.h>

#include <mark_recipes_for_execution.h>

#include <run_make_loop.h>

#include <heap/free.h>

#include <database/free.h>
#include <recipeset/free.h>

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
		int dirfd = AT_FDCWD;
		
		if (cmdln_directory && (dirfd = open(cmdln_directory, O_PATH)) < 0)
		{
			fprintf(stderr, "%s: error on chdir(\"%s\"): %m\n", argv0, cmdln_directory);
			exit(e_syscall_failed);
		}
		
		dpv(dirfd);
		
		struct recipeset* all_recipes = parse(dirfd, cmdln_makefile ?: "makefile");
		
		if (cmdln_print_dependency_tree)
		{
			print_dependency_tree(dirfd, all_recipes);
		}
		else
		{
			check_for_circular_dependencies(all_recipes);
			
			struct database* database = new_database(dirfd);
			
			database_cleanup(database);
			
			struct heap* ready = new_heap(compare_recipe_scores);
			
			determine_recipe_scores(all_recipes, ready, database);
			
			mark_recipes_for_execution(all_recipes, ready);
			
			run_make_loop(dirfd, all_recipes, ready, database);
			
			free_heap(ready);
			
			free_database(database);
		}
		
		free_recipeset(all_recipes);
		
		if (dirfd > 0)
			close(dirfd);
	}
	
	cmdln_free();
	
	EXIT;
	return 0;
}
























