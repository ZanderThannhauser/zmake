
#include <sys/types.h>

struct dirfd
{
	int fd;
	
	dev_t dev;
	ino_t ino;
	
	unsigned refcount;
};


