
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>

#include <debug.h>

#include <recipeset/add.h>

#include <recipe/new.h>
#include <recipe/add_depenency.h>
#include <recipe/free.h>

#include <recipeset/lookup.h>

#include <dirfd/struct.h>

#include "parse.h"
#include "zebu.h"

void parse(
	struct recipeset* all_recipes,
	struct dirfd* dirfd,
	const char* path)
{
	ENTER;
	
	dpv(dirfd->fd);
	dpvs(path);
	
	int fd = openat(dirfd->fd, path, O_RDONLY);
	
	if (fd < 0)
	{
		TODO;
		exit(1);
	}
	
	FILE* stream = fdopen(fd, "r");
	
	if (!stream)
	{
		TODO;
		exit(1);
	}
	
	// ready = new heap();
	// newly_added_recipes = set();
	// for grammar in zebu.parse():
		// read recipes:
			// substitute variables in target, depenencies and commands
			// if target in all_recipes:
				// check that it has no rules
			// otherwise:
				// create nwew
				// add to all_recipes and newly_added_recipes
			// any dependency that can't be found in all_recipes:
				// create new
		// variable assignments:
			// reassign value in scope
		// read includes:
			// if included file has recipe:
				// check_for_circular_dependencies(newly_added_recipes)
				// determine_recipe_scores(newly_added_recipes)
				// ready.push(included file)
				// mark_recipes_for_execution(ready)
				// run_make_loop(ready)
			// elif included file does not exist:
				// "error!"
			// parse(scope, included file)
			// newly_added_recipes.clear();
	// if len(newly_added_recipes):
		// check_for_circular_dependencies(newly_added_recipes)
		// determine_recipe_scores(newly_added_recipes)
	
	// free heap(ready)
	
	TODO;
	#if 0
	struct zebu_$start* start = zebu_parse(stream);
	
	struct zebu_root* root = start->root;
	
	for (unsigned i = 0, n = root->recipes.n; i < n; i++)
	{
		struct zebu_recipe* zrecipe = root->recipes.data[i];
		
		char* target = strdup((char*) zrecipe->target->data);
		
		dpvs(target);
		
		struct recipe* recipe = new_recipe(target, dirfd, zrecipe->commands);
		
		recipeset_add(all_recipes, recipe);
		
		free_recipe(recipe);
	}
	
	for (unsigned i = 0, n = root->recipes.n; i < n; i++)
	{
		struct zebu_recipe* zrecipe = root->recipes.data[i];
		
		const char* target = (char*) zrecipe->target->data;
		
		dpvs(target);
		
		struct recipe* recipe = recipeset_lookup(all_recipes, target, dirfd);
		
		assert(recipe);
		
		for (unsigned j = 0, m = zrecipe->depenencies.n; j < m; j++)
		{
			struct zebu_token* depenency_token = zrecipe->depenencies.data[j];
			
			const char* depenency = (char*) depenency_token->data;
			
			dpvs(depenency);
			
			struct recipe* dep_recipe = recipeset_lookup(all_recipes, depenency, dirfd);
			
			if (!dep_recipe)
			{
				TODO;
				exit(1);
			}
			
			recipe_add_depenency(recipe, dep_recipe);
		}
	}
	
	free_zebu_$start(start);
	#endif
	
	fclose(stream);
	
	EXIT;
}



































