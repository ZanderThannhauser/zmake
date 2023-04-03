
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <debug.h>

#include <recipe/struct.h>

#include <recipeset/lookup.h>

#include <dirfd/struct.h>

#include "struct.h"
#include "read_tests.h"

void database_read_tests(
	struct database* this,
	struct recipeset* all_recipes)
{
	ENTER;
	
	for (unsigned i = 0, n = this->header.n; i < n; i++)
	{
		struct database_record record = {};
		
		if (pread(this->fd, &record, sizeof(record), 0
			+ sizeof(struct database_header)
			+ sizeof(struct database_record)
			* ((this->header.i + i) % this->header.cap)) < 0)
		{
			TODO;
			exit(1);
		}
		
		dpvs(record.name);
		dpv(record.st_dev);
		dpv(record.st_ino);
		
		struct recipe* recipe = recipeset_lookup(
			all_recipes, record.name, &(struct dirfd){
				.st_dev = record.st_dev,
				.st_ino = record.st_ino,
			});
		
		if (recipe)
		{
			recipe->scores.total += record.passed;
			recipe->scores.count++;
		}
	}
	
	EXIT;
}





























