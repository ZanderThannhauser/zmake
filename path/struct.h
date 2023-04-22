
#include <limits.h>

struct path
{
	char name[NAME_MAX];
	
	struct path* parent;
	
	unsigned refcount;
};

