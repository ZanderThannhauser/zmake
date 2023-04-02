
#include <debug.h>

#include "struct.h"
#include "add_test_result.h"

void database_add_test_result(
	struct database* this,
	const char* target,
	bool passed)
{
	ENTER;
	
	dpvs(target);
	dpvb(passed);
	
	if (this->header.n == this->header.cap)
	{
		this->header.i = 0;
		this->header.cap = this->header.cap << 1 ?: 1;
	}
	
	time_t now = time(NULL);
	
	struct database_record record;
	
	strcpy(record.name, target);
	record.passed = passed;
	record.timestamp = now;
	
	if (pwrite(this->fd, &record, sizeof(record), 0
		+ sizeof(struct database_header)
		+ sizeof(struct database_record)
		* ((this->header.i + this->header.n++) % this->header.cap))
		< sizeof(struct database_record))
	{
		TODO;
		exit(1);
	}
	
	EXIT;
}











