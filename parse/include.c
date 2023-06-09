
#include <stdlib.h>
#include <debug.h>

#include <memory/srealloc.h>

#include <recipeset/new.h>
#include <recipeset/lookup.h>
#include <recipeset/len.h>
#include <recipeset/clear.h>
#include <recipeset/add.h>
#include <recipeset/free.h>

#include <check_for_circular_dependencies.h>

#include <propagate_ftimes.h>

#include <mark_recipes_for_execution.h>

#include <run_make_loop.h>

#include "evaluate/argument.h"

#include "zebu.h"
#include "recursive.h"
#include "include.h"

void evaluate_include_statement(
	struct zebu_include* include,
	struct recipeset* all_recipes,
	struct recipeset* propagate_ftimes_start,
	struct database* database,
	struct dirfd* absolute_dirfd,
	struct dirfd* local_dirfd,
	struct scope* scope)
{
	ENTER;
	
	struct {
		char** data;
		unsigned n, cap;
	} files = {};
	
	struct recipeset* start = new_recipeset(false);
	
	evaluate_argument(include->argument, scope, ({
		void callback(char* file)
		{
			dpvs(file);
			
			struct recipe* recipe = recipeset_lookup(all_recipes, file, absolute_dirfd);
			
			if (recipe)
				recipeset_add(start, recipe);
			
			if (files.n == files.cap)
			{
				files.cap = files.cap << 1 ?: 1;
				files.data = srealloc(files.data, sizeof(*files.data) * files.cap);
			}
			
			files.data[files.n++] = file;
		}
		callback;
	}));
	
	if (recipeset_len(start))
	{
		check_for_circular_dependencies(all_recipes);
		
		if (recipeset_len(propagate_ftimes_start))
		{
			propagate_ftimes(propagate_ftimes_start);
			recipeset_clear(propagate_ftimes_start);
		}
		
		mark_recipes_for_execution(start);
		
		run_make_loop(all_recipes, database);
	}
	
	for (unsigned i = 0; i < files.n; i++)
	{
		char* file = files.data[i];
		
		recursive_parse(
			/* struct database* database: */ database,
			/* struct recipeset* all_recipes: */ all_recipes,
			/* struct recipeset* propagate_ftimes: */ propagate_ftimes_start,
			/* struct dirfd* absolute_dirfd: */ absolute_dirfd,
			/* struct dirfd* local_dirfd: */ local_dirfd,
			/* struct scope* scope: */ scope,
			/* const char* path: */ file);
		
		free(file);
	}
	
	free(files.data);
	
	free_recipeset(start);
	
	EXIT;
}













