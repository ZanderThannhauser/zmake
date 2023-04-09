
const char* cmdln_usage_message = ""
	"usage: zmake" "\n"
	
	"\t" "-C path" "\n"
	"\t" "--directory=path" "\n"
	"\t" "\t" "Change to directory dir before reading the makefiles or doing " "\n"
	"\t" "\t" "anything else." "\n"
	
	"\t" "-f file" "\n"
	"\t" "\t" "Use file as a makefile." "\n"
	
	"\t" "-j jobs" "\n"
	"\t" "--jobs=jobs" "\n"
	"\t" "\t" "Specifies the number of jobs (commands) to run "
	"\t" "\t" "simultaneously." "\n"
			
	"\t" "-B" "\n"
	"\t" "--simulate-clean" "\n"
	"\t" "\t" "Unconditionally make all targets." "\n"
			
	"\t" "-n" "\n"
	"\t" "--dry-run" "\n"
	"\t" "\t" "Print the commands that would be executed, but do not " "\n"
	"\t" "\t" "execute them (except in certain circumstances)." "\n"
				
	"\t" "-p" "\n"
	"\t" "--print-dependency-tree" "\n"
	"\t" "\t" "Instead of building, generate a graphviz file depicting" "\n"
	"\t" "\t" "the dependency tree, and which recipes would be built." "\n"
				
	"\t" "-v" "\n"
	"\t" "--verbose" "\n"
	"\t" "\t" "make zmake more verbose." "\n"
			
	"\t" "-h" "\n"
	"\t" "--help" "\n"
	"\t" "\t" "print this help message." "\n"
"";

