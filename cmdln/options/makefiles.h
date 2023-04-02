
extern struct cmdln_makefiles_list {
	struct cmdln_makefile_bundle {
		const char* chdir;
		struct cmdln_makefile_bundle_list {
			const char** data;
			unsigned n, cap;
		} targets, makefiles;
	}* data;
	unsigned n, cap;
} cmdln_makefiles;

