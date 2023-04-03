
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

#include <debug.h>

#include <recipeset/foreach.h>

#include <recipe/struct.h>

#include <misc/hsv_to_rgb.h>

#include "print_dependency_tree.h"

void print_dependency_tree(
	struct recipeset* all_recipes)
{
	ENTER;
	
	FILE* stream = fopen("dependency-tree.dot", "w");
	
	if (!stream)
	{
		TODO;
		exit(1);
	}
	
	fprintf(stream, "digraph {" "\n");
	
	fprintf(stream, ""
		"rankdir = LR;" "\n"
		"bgcolor = black;" "\n"
	"");
	
	recipeset_foreach(all_recipes, ({
		void callback(struct recipe* recipe)
		{
			const char* target = recipe->target;
			
			struct dirfd* dirfd = recipe->dirfd;
			
			struct rgb real_color = {128, 128, 128};
			
			struct rgb effective_color = {128, 128, 128};
			
			if (recipe->scores.real < INFINITY)
				real_color = hsv_to_rgb((recipe->scores.real * 2 * M_PI) / 3, 0.9, 1);
			
			if (recipe->scores.effective < INFINITY)
				effective_color = hsv_to_rgb((recipe->scores.effective * 2 * M_PI) / 3, 0.9, 1);
			
			fprintf(stream, ""
				"\"%s:%p\" [" "\n"
					"label = \"%s\";" "\n"
					"style = filled;" "\n"
					"shape = box;" "\n"
					"peripheries = %u;" "\n"
					"fillcolor = \"#%20hhX%20hhX%20hhX\";" "\n"
					"color = \"#%20hhX%20hhX%20hhX\";" "\n"
				"];" "\n"
			"",
			target, dirfd,
			target,
			recipe->execution.marked ? 2 : 1,
			real_color.red, real_color.green, real_color.blue,
			effective_color.red, effective_color.green, effective_color.blue);
			
			recipeset_foreach(recipe->dep_on, ({
				void callback(struct recipe* dependency)
				{
					fprintf(stream, ""
						"\"%s:%p\" -> \"%s:%p\" [" "\n"
							"color = white;" "\n"
						"];" "\n"
					"", target, dirfd, dependency->target, dependency->dirfd);
				}
				callback;
			}));
		}
		callback;
	}));
	
	fprintf(stream, "}" "\n");
	
	fclose(stream);
	
	EXIT;
}


















