
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <sys/time.h>

#include <debug.h>

#include <enums/error.h>

#include <memory/srealloc.h>

#include "options/makefiles.h"
#include "options/jobs.h"
#include "options/always_make.h"
#include "options/dry_run.h"
#include "options/print_dependency_tree.h"
#include "options/verbose.h"
#include "options/help.h"
#include "usage.h"
#include "process.h"

static void append_chdir(const char* chdir)
{
	ENTER;
	
	dpvs(chdir);
	
	if (cmdln_makefiles.n == cmdln_makefiles.cap)
	{
		cmdln_makefiles.cap = cmdln_makefiles.cap << 1 ?: 1;
		cmdln_makefiles.data = srealloc(cmdln_makefiles.data,
			sizeof(*cmdln_makefiles.data) * cmdln_makefiles.cap);
	}
	
	cmdln_makefiles.data[cmdln_makefiles.n++] = (struct cmdln_makefile_bundle) {
		.chdir = chdir,
	};
	
	EXIT;
}

static void append_target(unsigned index, const char* target)
{
	ENTER;
	
	dpvs(target);
	
	assert(index < cmdln_makefiles.n);
	
	struct cmdln_makefile_bundle_list* list = &cmdln_makefiles.data[index].targets;
	
	if (list->n == list->cap)
	{
		list->cap = list->cap << 1 ?: 1;
		list->data = srealloc(list->data, sizeof(*list->data) * list->cap);
	}
	
	list->data[list->n++] = target;
	
	EXIT;
}

static void append_makefile(unsigned index, const char* makefile)
{
	ENTER;
	
	dpvs(makefile);
	
	assert(index < cmdln_makefiles.n);
	
	struct cmdln_makefile_bundle_list* list = &cmdln_makefiles.data[index].makefiles;
	
	if (list->n == list->cap)
	{
		list->cap = list->cap << 1 ?: 1;
		list->data = srealloc(list->data, sizeof(*list->data) * list->cap);
	}
	
	list->data[list->n++] = makefile;
	
	EXIT;
}

void cmdln_process(int argc, char* const* argv)
{
	ENTER;
	
	for (int i = 1; i < argc;)
	{
		char* arg = argv[i++];
		
		dpvs(arg);
		
		if (arg[0] != '-')
		{
			dpvs(arg);
			
			if (!cmdln_makefiles.n)
				append_chdir(".");
			
			append_target(cmdln_makefiles.n - 1, arg);
		}
		else switch (arg[1])
		{
			case '-':
				if (!strncmp(arg + 2, "directory", 8)) {
					optarg = (arg[2 + 8] == '=') ? &arg[2 + 8 + 1] : argv[i++];
					goto directory;
				} else if (!strncmp(arg + 2, "makefile", 8)) {
					optarg = (arg[2 + 8] == '=') ? &arg[2 + 8 + 1] : argv[i++];
					goto makefile;
				} else if (!strncmp(arg + 2, "jobs", 4)) {
					optarg = (arg[2 + 4] == '=') ? &arg[2 + 4 + 1] : argv[i++];
					goto jobs;
				} else if (!strncmp(arg + 2, "simulate-clean", 14))
					goto always_make;
				else if (!strncmp(arg + 2, "dry-run", 7))
					goto dry_run;
				else if (!strncmp(arg + 2, "print-dependency-tree", 21))
					goto print_dependency_tree;
				else if (!strncmp(arg + 2, "verbose", 7))
					goto verbose;
				else if (!strncmp(arg + 2, "help", 4))
					goto help;
				else
				{
					TODO;
				}
			
			case 'C':
				optarg = arg[2] ? &arg[2] : argv[i++];
			directory:
				if (!optarg)
				{
					TODO;
					exit(e_bad_cmdline_args);
				}
				
				append_chdir(optarg);
				break;
			
			case 'f':
				optarg = arg[2] ? &arg[2] : argv[i++];
			makefile:
				if (!optarg)
				{
					TODO;
					exit(e_bad_cmdline_args);
				}
				
				if (!cmdln_makefiles.n)
					append_chdir(".");
				
				append_makefile(cmdln_makefiles.n - 1, optarg);
				break;
			
			char* m;
			unsigned long number;
			case 'j':
				optarg = arg[2] ? &arg[2] : argv[i++];
			jobs:
				if (optarg)
				{
					dpvs(optarg);
					
					errno = 0;
					
					number = strtoul(optarg, &m, 10);
					
					if (errno || *m || number > UINT_MAX)
					{
						TODO;
						exit(e_bad_cmdline_args);
					}
					
					cmdln_jobs = number;
				}
				else
					cmdln_jobs = 8;
				
				dpv(cmdln_jobs);
				break;
			
			case 'B':
			always_make:
				cmdln_always_make = true;
				dpvb(cmdln_always_make);
				break;
			
			case 'n':
			dry_run:
				cmdln_dry_run = true;
				dpvb(cmdln_dry_run);
				break;
			
			case 'p':
			print_dependency_tree:
				cmdln_print_dependency_tree = true;
				dpvb(cmdln_print_dependency_tree);
				break;
			
			case 'v':
			verbose:
				cmdln_verbose = true;
				dpvb(cmdln_verbose);
				break;
			
			case 'h':
			help:
				cmdln_help = true;
				dpvb(cmdln_help);
				break;
			
			default:
				TODO;
				break;
		}
	}
	
	if (!cmdln_makefiles.n)
		append_chdir(".");
	
	for (int i = 0, n = cmdln_makefiles.n; i < n; i++)
	{
		if (!cmdln_makefiles.data[i].makefiles.n)
			append_makefile(i, "makefile");
		if (!cmdln_makefiles.data[i].targets.n)
			append_target(i, "default");
	}
	
	#if 0
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
				break;
			}
			
			case 'B':
				cmdln_always_make = true;
				dpvb(cmdln_always_make);
				break;
			
			case 'n':
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
	#endif
	
	EXIT;
}

















