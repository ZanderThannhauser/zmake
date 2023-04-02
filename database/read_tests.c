
#include <debug.h>

#include <recipe/struct.h>

#include <recipeset/lookup.h>

#include "struct.h"
#include "read_tests.h"

void database_read_tests(
	struct database* this,
	struct recipeset* all_recipes)
{
	ENTER;
	
	struct database_record record;
	
	for (unsigned i = 0, n = this->header.n; i < n; i++)
	{
		if (pread(this->fd, &record, sizeof(record), 0
			+ sizeof(struct database_header)
			+ sizeof(struct database_record)
			* ((this->header.i + i) % this->header.cap)) < PATH_MAX)
		{
			TODO;
			exit(1);
		}
		
		dpvs(record.name);
		
		struct recipe* recipe = recipeset_lookup(all_recipes, record.name);
		
		if (recipe)
		{
			recipe->scores.total += record.passed;
			recipe->scores.count++;
		}
	}
	
	EXIT;
}


















