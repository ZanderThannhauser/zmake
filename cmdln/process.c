
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <sys/time.h>

#include <debug.h>

#include <enums/error.h>

#include "options/directory.h"
#include "options/makefile.h"
#include "options/jobs.h"
#include "options/always_make.h"
#include "options/dry_run.h"
#include "options/print_dependency_tree.h"
#include "options/targets.h"
#include "options/verbose.h"
#include "options/help.h"
#include "usage.h"
#include "process.h"

void cmdln_process(int argc, char* const* argv)
{
	ENTER;
	
	int opt, option_index;
	const struct option long_options[] = {
		{"directory",       required_argument, 0, 'C'},
		{"makefile",        required_argument, 0, 'f'},
		{"jobs",            required_argument, 0, 'j'},
		
		{"always-make",           no_argument, 0, 'B'},
		{"dry-run",               no_argument, 0, 'n'},
		{"print-dependency-tree", no_argument, 0, 'p'},
		{"verbose",               no_argument, 0, 'v'},
		{"help",                  no_argument, 0, 'h'},
		{ 0,                                0, 0,  0 },
	};
	
	while ((opt = getopt_long(argc, argv,
		"C:"
		"f:"
		"j:"
		"B"
		"n"
		"p"
		"v"
		"h",
		long_options, &option_index)) >= 0)
	{
		switch (opt)
		{
			// matching options:
			case 'C':
				cmdln_directory = optarg;
				dpvs(cmdln_directory);
				break;
			
			case 'f':
				cmdln_makefile = optarg;
				dpvs(cmdln_makefile);
				break;
			
			case 'j':
			{
				dpvs(optarg);
				
				char* m;
				
				errno = 0;
				
				unsigned long number = strtoul(optarg, &m, 10);
				
				if (errno || *m || number > UINT_MAX)
				{
					TODO;
					exit(1);
				}
				
				cmdln_jobs = number;
				
				dpv(cmdln_jobs);
				break;
			}
			
			case 'B':
				cmdln_always_make = true;
				dpvb(cmdln_always_make);
				break;
			
			case 'n':
				cmdln_dry_run = true;
				dpvb(cmdln_dry_run);
				break;
			
			case 'p':
				cmdln_print_dependency_tree = true;
				dpvb(cmdln_print_dependency_tree);
				break;
			
			case 'v':
				cmdln_verbose = true;
				dpvb(cmdln_verbose);
				break;
			
			case 'h':
				cmdln_help = true;
				dpvb(cmdln_help);
				break;
			
			default:
				fputs(cmdln_usage_message, stdout);
				exit(e_bad_cmdline_args);
				break;
		}
	}
	
	const char* target;
	while ((target = argv[optind++]))
	{
		dpvs(target);
		
		if (cmdln_targets.n == cmdln_targets.cap)
		{
			cmdln_targets.cap = cmdln_targets.cap << 1 ?: 1;
			cmdln_targets.data = srealloc(
				cmdln_targets.data,
				sizeof(*cmdln_targets.data) * cmdln_targets.cap);
		}
		
		cmdln_targets.data[cmdln_targets.n++] = target;
	}
	
	EXIT;
}

















