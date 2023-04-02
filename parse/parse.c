
#include <debug.h>

#include <recipeset/new.h>
#include <recipeset/add.h>

#include <recipe/new.h>
#include <recipe/add_depenency.h>
#include <recipe/free.h>

#include <recipeset/lookup.h>

#include "parse.h"
#include "zebu.h"

struct recipeset* parse(
	int dirfd,
	const char* path)
{
	ENTER;
	
	dpv(dirfd);
	dpvs(path);
	
	int fd = openat(dirfd, path, O_RDONLY);
	
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
	
	struct zebu_$start* start = zebu_parse(stream);
	
	struct zebu_root* root = start->root;
	
	struct recipeset* all_recipes = new_recipeset(true);
	
	for (unsigned i = 0, n = root->recipes.n; i < n; i++)
	{
		struct zebu_recipe* zrecipe = root->recipes.data[i];
		
		char* target = strdup((char*) zrecipe->target->data);
		
		dpvs(target);
		
		struct recipe* recipe = new_recipe(target, zrecipe->commands);
		
		recipeset_add(all_recipes, recipe);
		
		free_recipe(recipe);
	}
	
	for (unsigned i = 0, n = root->recipes.n; i < n; i++)
	{
		struct zebu_recipe* zrecipe = root->recipes.data[i];
		
		const char* target = (char*) zrecipe->target->data;
		
		dpvs(target);
		
		struct recipe* recipe = recipeset_lookup(all_recipes, target);
		
		assert(recipe);
		
		for (unsigned j = 0, m = zrecipe->depenencies.n; j < m; j++)
		{
			struct zebu_token* depenency_token = zrecipe->depenencies.data[j];
			
			const char* depenency = (char*) depenency_token->data;
			
			dpvs(depenency);
			
			struct recipe* dep_recipe = recipeset_lookup(all_recipes, depenency);
			
			if (!dep_recipe)
			{
				TODO;
				exit(1);
			}
			
			recipe_add_depenency(recipe, dep_recipe);
		}
	}
	
	free_zebu_$start(start);
	
	fclose(stream);
	
	EXIT;
	return all_recipes;
}



































