
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_database(
	struct database* this)
{
	ENTER;
	
	if (true
		&& (false
			|| this->header.i       != this->original_header.i
			|| this->header.n       != this->original_header.n
			|| this->header.cap     != this->original_header.cap
			|| this->header.too_old != this->original_header.too_old)
		&& pwrite(this->fd, &this->header, sizeof(this->header), 0) < sizeof(this->header))
	{
		TODO;
		exit(1);
	}
	
	close(this->fd);
	
	free(this);
	
	EXIT;
}

