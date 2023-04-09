
#include <stdlib.h>
#include <assert.h>
#include <debug.h>

#include <parse/zebu.h>

#include <commands/len.h>
#include <commands/new.h>
#include <commands/append.h>
#include <commands/inc.h>
#include <commands/free.h>
#include <commands/command/struct.h>
#include <commands/command/new.h>
#include <commands/command/append.h>
#include <commands/command/simple/new.h>
#include <commands/command/simple/append.h>

#include <recipe/struct.h>
#include <recipe/new.h>
#include <recipe/add_depenency.h>
#include <recipe/add_ordered_depenency.h>
#include <recipe/free.h>

#include <recipeset/foreach.h>
#include <recipeset/len.h>
#include <recipeset/new.h>
#include <recipeset/lookup.h>
#include <recipeset/free.h>
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
	
	struct recipeset* dependencies = new_recipeset(false);
	
	if (zrecipe->dependencies.n)
	{
		for (unsigned i = 0, n = zrecipe->dependencies.n; i < n; i++)
		{
			struct zebu_argument* zdep = zrecipe->dependencies.data[i];
			
			evaluate_argument(zdep, scope, ({
				void callback(char* dependency)
				{
					dpvs(dependency);
					
					struct recipe* dep_recipe = lookup_or_create(dependency);
					
					recipeset_add(dependencies, dep_recipe);
					
					free(dependency);
				}
				callback;
			}));
		}
	}
	
	struct recipeset* ordered = new_recipeset(false);
	
	if (zrecipe->ordered.n)
	{
		for (unsigned i = 0, n = zrecipe->ordered.n; i < n; i++)
		{
			struct zebu_argument* zdep = zrecipe->ordered.data[i];
			
			evaluate_argument(zdep, scope, ({
				void callback(char* dependency)
				{
					dpvs(dependency);
					
					struct recipe* dep_recipe = lookup_or_create(dependency);
					
					recipeset_add(ordered, dep_recipe);
					
					free(dependency);
				}
				callback;
			}));
		}
	}
	
	struct commands* commands = new_commands();
	
	if (zrecipe->commands)
	{
		struct zebu_commands* zcommands = zrecipe->commands;
		
		for (unsigned i = 0, n = zcommands->commands.n; i < n; i++)
		{
			struct zebu_command* zcommand = zcommands->commands.data[i];
			
			struct command* command = new_command();
			
			for (unsigned j = 0, m = zcommand->simples.n; j < m; j++)
			{
				struct zebu_simple_command* zsimple = zcommand->simples.data[j];
				
				struct simple_command* simple = new_simple_command();
				
				for (unsigned k = 0, o = zsimple->args.n; k < o; k++)
				{
					struct zebu_argument* zarg = zsimple->args.data[k];
					
					evaluate_argument(zarg, scope, ({
						void callback(char* arg) {
							simple_command_append(simple, arg);
						}
						callback;
					}));
				}
				
				command_append(command, simple);
			}
			
			if (zcommand->redirect_in)
			{
				evaluate_argument(zcommand->redirect_in, scope, ({
					void callback(char* arg) {
						if (command->redirect_in)
						{
							TODO;
							exit(1);
						}
						command->redirect_in = arg;
					}
					callback;
				}));
			}
			
			if (zcommand->redirect_out)
			{
				evaluate_argument(zcommand->redirect_out, scope, ({
					void callback(char* arg) {
						if (command->redirect_out)
						{
							TODO;
							exit(1);
						}
						command->redirect_out = arg;
					}
					callback;
				}));
			}
			
			commands_append(commands, command);
		}
	}
	
	for (unsigned i = 0, n = zrecipe->targets.n; i < n; i++)
	{
		struct zebu_argument* ztarget = zrecipe->targets.data[i];
		
		evaluate_argument(ztarget, scope, ({
			void callback(char* target)
			{
				dpvs(target);
				
				struct recipe* recipe = lookup_or_create(target);
				
				if (recipeset_len(dependencies) || recipeset_len(ordered))
				{
					recipeset_foreach(dependencies, ({
						void callback(struct recipe* dep) {
							recipe_add_depenency(recipe, dep);
						}
						callback;
					}));
					
					recipeset_foreach(ordered, ({
						void callback(struct recipe* dep) {
							recipe_add_ordered_depenency(recipe, dep);
						}
						callback;
					}));
					
					recipeset_add(propagate_ftimes, recipe);
				}
				
				if (commands_len(commands))
				{
					if (recipe->commands)
					{
						// recipe already has commands!
						TODO;
						exit(1);
					}
					
					recipe->commands = inc_commands(commands);
				}
				
				free(target);
			}
			callback;
		}));
	}
	
	free_recipeset(dependencies);
	
	free_recipeset(ordered);
	
	free_commands(commands);
	
	EXIT;
}












