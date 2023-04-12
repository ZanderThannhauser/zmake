
#include <time.h>
#include <stdbool.h>

struct recipe
{
	char* target; // must be the first
	struct dirfd* dirfd; // must be the second
	
	struct recipeset*  dep_on; // I am dependant on these
	struct recipeset* odep_on; // I am dependant on these (order only)
	struct recipeset*  dep_of; // these are dependant on me
	
	struct {
		unsigned checked;
		bool visited;
	} circular;
	
	struct {
		time_t real, effective;
	} ftimes;
	
	struct {
		unsigned round;
		unsigned waiting;
	} execution;
	
	struct commands* commands;
	
	unsigned refcount;
};

















