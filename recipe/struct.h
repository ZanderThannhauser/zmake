
#include <time.h>
#include <stdbool.h>

struct zebu_commands;

struct recipe
{
	char* target; // must be the first
	struct dirfd* dirfd; // must be the second
	
	struct recipeset* dep_on; // I am dependant on these
	struct recipeset* dep_of; // these are dependant on me
	
	struct {
		unsigned checked;
		bool visited;
	} circular;
	
	struct {
		time_t real, effective;
	} ftimes;
	
	struct {
		unsigned round;
		bool marked;
		unsigned waiting;
	} execution;
	
	struct {
		struct command** data;
		unsigned n, cap;
	} commands;
	
	unsigned refcount;
};

















