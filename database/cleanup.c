
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <unistd.h>
#include <debug.h>

#include "struct.h"
#include "cleanup.h"

void database_cleanup(
	struct database* this)
{
	ENTER;
	
	time_t get_timestamp()
	{
		time_t time;
		
		if (pread(this->fd, &time, sizeof(time), 0
			+ sizeof(struct database_header)
			+ sizeof(struct database_record) * (this->header.i % this->header.cap)
			+ offsetof(struct database_record, timestamp)) < sizeof(time))
		{
			TODO;
			exit(1);
		}
		
		return time;
	}
	
	time_t now = time(NULL);
	
	dpv(now);
	
	time_t cutoff = now - 14 * 24 * 60 * 60;
	
	dpv(this->header.n);
	
	while (this->header.n && get_timestamp() < cutoff)
		this->header.n--, this->header.i++;
	
	EXIT;
}











