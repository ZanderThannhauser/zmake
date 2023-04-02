
struct zebu_commands;

struct recipe
{
	char* target; // must be the first
	
	struct recipeset* dep_on; // I am dependant on these
	struct recipeset* dep_of; // these are dependant on me
	
	struct zebu_commands *commands;
	
	struct {
		bool checked, visited;
	} circular;
	
	struct {
		unsigned total, count;
		
		long double real, effective;
	} scores;
	
	struct {
		bool marked;
		unsigned waiting;
	} execution;
	
	unsigned refcount;
};

