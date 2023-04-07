
#include <stdlib.h>
#include <assert.h>
#include <debug.h>

#include <parse/zebu.h>

#include <command/struct.h>
#include <command/new.h>
#include <command/append.h>
#include <command/simple/new.h>
#include <command/simple/append.h>

#include <recipe/struct.h>
#include <recipe/new.h>
#include <recipe/add_command.h>
#include <recipe/add_depenency.h>
#include <recipe/free.h>

#include <recipeset/lookup.h>
#include <recipeset/add.h>

#include <database/lookup.h>

#include "evaluate/argument.h"
#include "evaluate/string.h"

#include "recipe.h"

void evaluate_recipe_statement(
	struct zebu_recipe* zrecipe,
	struct recipeset* all_recipes,
	struct recipeset* propagate_ftimes,
	struct database* database,
	struct dirfd* dirfd,
	struct scope* scope)
{
	ENTER;
	
	struct recipe* lookup_or_create(char* target)
	{
		struct recipe* recipe = recipeset_lookup(all_recipes, target, dirfd);
		
		if (!recipe)
		{
			recipe = new_recipe(target, dirfd);
			
			time_t ftime = database_lookup(database, target, dirfd);
			
			recipe->ftimes.real = ftime;
			recipe->ftimes.effective = ftime;
			
			recipeset_add(propagate_ftimes, recipe);
			recipeset_add(all_recipes, recipe);
			
			free_recipe(recipe);
		}
		
		return recipe;
	}
	
	char* target = evaluate_argument(zrecipe->target, scope);
	
	dpvs(target);
	
	struct recipe* recipe = lookup_or_create(target);
	
	if (zrecipe->commands)
	{
		if (recipe->commands.n)
		{
			// recipe already has commands!
			TODO;
			exit(1);
		}
		
		if (zrecipe->commands)
		{
			struct zebu_commands* commands = zrecipe->commands;
			
			for (unsigned i = 0, n = commands->commands.n; i < n; i++)
			{
				struct zebu_command* zcommand = commands->commands.data[i];
				
				struct command* command = new_command();
				
				for (unsigned j = 0, m = zcommand->simples.n; j < m; j++)
				{
					struct zebu_simple_command* zsimple = zcommand->simples.data[j];
					
					struct simple_command* simple = new_simple_command();
					
					for (unsigned k = 0, o = zsimple->args.n; k < o; k++)
					{
						struct zebu_argument* zarg = zsimple->args.data[k];
						
						char* arg = evaluate_argument(zarg, scope);
						
						simple_command_append(simple, arg);
					}
					
					command_append(command, simple);
				}
				
				if (zcommand->redirect_in)
				{
					command->redirect_in = evaluate_argument(zcommand->redirect_in, scope);
				}
				
				if (zcommand->redirect_out)
				{
					command->redirect_out = evaluate_argument(zcommand->redirect_out, scope);
				}
				
				recipe_add_command(recipe, command);
			}
		}
	}
	
	if (zrecipe->dependencies.n)
	{
		for (unsigned i = 0, n = zrecipe->dependencies.n; i < n; i++)
		{
			struct zebu_argument* zdep = zrecipe->dependencies.data[i];
			
			char* dependency = evaluate_argument(zdep, scope);
			
			dpvs(dependency);
			
			struct recipe* dep_recipe = lookup_or_create(dependency);
			
			recipe_add_depenency(recipe, dep_recipe);
			
			free(dependency);
		}
		
		recipeset_add(propagate_ftimes, recipe);
	}
	
	free(target);
	
	EXIT;
}









