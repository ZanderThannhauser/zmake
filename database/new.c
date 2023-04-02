
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct database* new_database(
	int dirfd)
{
	ENTER;
	
	struct database* this = smalloc(sizeof(*this));
	
	int fd = openat(dirfd, ".zmake.db", O_RDWR | O_CREAT, 0664);
	
	errno = 0;
	
	if (read(fd, &this->header, sizeof(this->header)) < sizeof(this->header))
	{
		if (errno)
		{
			TODO;
			exit(1);
		}
		else
		{
			// brand new (empty) file
			this->header = (struct database_header) {0, 0, 0};
		}
	}
	else
	{
		; // file opened normally; nothing to do
	}
	
	this->original_header = this->header;
	
	this->fd = fd;
	
	EXIT;
	return this;
}

