
#include <stdbool.h>

struct zebu_commands;

struct recipe
{
	char* target; // must be the first
	struct dirfd* dirfd;
	
	struct recipeset* dep_on; // I am dependant on these
	struct recipeset* dep_of; // these are dependant on me
	
	struct zebu_commands *commands;
	
	struct {
		bool checked, visited;
	} circular;
	
	struct {
		unsigned total, count;
		
		double real, effective;
	} scores;
	
	struct {
		unsigned round;
		bool marked;
		unsigned waiting;
	} execution;
	
	unsigned refcount;
};

















