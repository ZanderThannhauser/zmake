
#ifndef RELEASE
	#include <assert.h>
	#include <stdio.h>
	#include <dirent.h>
	#include <sys/sendfile.h>
	#include <sched.h>
	#include <stdlib.h>
	#include <sys/mount.h>
	#include <locale.h>
	#include <valgrind/memcheck.h>
	#include <string.h>
	#include <getopt.h>
	#include <ftw.h>
	#include <unistd.h>
	#include <wchar.h>
	#include <errno.h>
	#include <stdarg.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <inttypes.h>
	#include <fcntl.h>
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <stdbool.h>
	#include <linux/limits.h>
	#include <time.h>
	#include <limits.h>
	#include <sys/param.h>
	
	#include <defines/argv0.h>

	#include <enums/error.h>

	#include <memory/smalloc.h>
	#include <memory/srealloc.h>
	
	struct dirfd;
	struct scope;
	struct recipeset;
	struct zebu_target;
	struct database;
	struct recipe;
	struct heap;
	struct zebu_include;
	struct zebu_argument;
	struct zebu_statement;
	struct simple_command;
	struct zebu_conditional;
	struct value;
	struct zebu_print;
	struct commands;
	struct zebu_primary_expression;
	struct command;
	struct zebu_assignments;
	struct list_value;
	struct set_value;
	
	#ifdef DEBUGGING
		extern int debug_depth;
		
		#define TODO \
		{\
			assert(debug_depth >= 0); \
			printf("%*sTODO: File: %s: Line: %i\n", debug_depth, "", \
				__FILE__, __LINE__);\
			char buffer[100];\
			sprintf(buffer, "+%i", __LINE__);\
			execlp("gedit", "gedit", __FILE__, buffer, NULL);\
			abort(); \
		}
		
		#define CHECK TODO
		#define NOPE CHECK
		#define HERE \
			printf("%*sHERE: File: %s: Line: %i\n", debug_depth, "", __FILE__, __LINE__);
		
		#define ENTER \
			assert(debug_depth >= 0), \
			printf("%*s<%s>\n", debug_depth++, "", __PRETTY_FUNCTION__);
		
		#define EXIT \
			assert(--debug_depth >= 0), \
			printf("%*s</%s>\n", debug_depth, "", __PRETTY_FUNCTION__);
		
		#define dpv(val) dprint(val)
		
		#define dpvb(b) \
			assert(debug_depth >= 0),\
			printf("%*s" #b " == %s\n", debug_depth, "", (b) ? "true" : "false");
		
		#define dpvc(ch) \
			assert(debug_depth >= 0),\
			printf("%*s" #ch " == '%c'\n", debug_depth, "", ch);
		
		#define dpvs(str) \
			assert(debug_depth >= 0), \
			printf((_Generic(str, \
				char*:    "%*s" #str " == " "\"%s\"\n", \
				const char*:    "%*s" #str " == " "\"%s\"\n", \
				wchar_t*: "%*s" #str " == " "L\"%ls\"\n", \
				const wchar_t*: "%*s" #str " == " "L\"%ls\"\n", \
				default:  "%*s" #str " == " "(unknown) %p\n")), \
				debug_depth, "", str);
		
		#define dpvsn(str, len) \
			assert(debug_depth >= 0), \
			printf((_Generic(str, \
				char*:    "%*s" #str " == " "\".*%s\"\n", \
				const char*:    "%*s" #str " == " "\".*%s\"\n", \
				wchar_t*: "%*s" #str " == " "L\"%.*ls\"\n", \
				const wchar_t*: "%*s" #str " == " "L\"%.*ls\"\n", \
				default:  "%*s" #str " == " "(unknown) %i,%p\n")), \
				debug_depth, "", (int) len, str);
		
		#define dperror(val) \
			assert(debug_depth >= 0),\
			printf("%*s"#val" == %s (%s)\n", \
				debug_depth, "", \
				(const char*[]){ \
					[0] = "0", \
					[EPERM] = "EPERM", \
					[ENOENT] = "ENOENT", \
					[ESRCH] = "ESRCH", \
					[EINTR] = "EINTR", \
					[EIO] = "EIO", \
					[ENXIO] = "ENXIO", \
					[E2BIG] = "E2BIG", \
					[ENOEXEC] = "ENOEXEC", \
					[EBADF] = "EBADF", \
					[ECHILD] = "ECHILD", \
					[EAGAIN] = "EAGAIN", \
					[ENOMEM] = "ENOMEM", \
					[EACCES] = "EACCES", \
					[EFAULT] = "EFAULT", \
					[ENOTBLK] = "ENOTBLK", \
					[EBUSY] = "EBUSY", \
					[EEXIST] = "EEXIST", \
					[EXDEV] = "EXDEV", \
					[ENODEV] = "ENODEV", \
					[ENOTDIR] = "ENOTDIR", \
					[EISDIR] = "EISDIR", \
					[EINVAL] = "EINVAL", \
					[ENFILE] = "ENFILE", \
					[EMFILE] = "EMFILE", \
					[ENOTTY] = "ENOTTY", \
					[ETXTBSY] = "ETXTBSY", \
					[EFBIG] = "EFBIG", \
					[ENOSPC] = "ENOSPC", \
					[ESPIPE] = "ESPIPE", \
					[EROFS] = "EROFS", \
					[EMLINK] = "EMLINK", \
					[EPIPE] = "EPIPE", \
					[EDOM] = "EDOM", \
					[ERANGE] = "ERANGE", \
					[EHWPOISON] = "EHWPOISON", \
				}[val] ?: "???", \
				strerror(val));
		
		#define dpvo(val) \
			assert(debug_depth >= 0),\
			printf((_Generic(val, \
				signed char:    "%*s" #val " == " "(signed char) 0%hho\n", \
				unsigned char:  "%*s" #val " == " "(unsigned char) 0%hho\n", \
				signed short:   "%*s" #val " == " "(signed short) 0%ho\n", \
				unsigned short: "%*s" #val " == " "(unsigned char) 0%ho\n", \
				signed int:     "%*s" #val " == " "(signed int) 0%o\n", \
				unsigned int:   "%*s" #val " == " "(unsigned int) 0%o\n", \
				signed long:    "%*s" #val " == " "(signed long) 0%lo\n", \
				unsigned long:  "%*s" #val " == " "(unsigned long) 0%lo\n", \
				float:          "%*s" #val " == " "(float) %#a\n", \
				double:         "%*s" #val " == " "(double) %#la\n", \
				long double:    "%*s" #val " == " "(long double) %#La\n", \
				default:        "%*s" #val " == " "(void*) %#p\n")), \
				debug_depth, "", val);
		
		#define dpvx(val) \
			assert(debug_depth >= 0),\
			printf((_Generic(val, \
				signed char:    "%*s" #val " == " "(signed char) 0x%hhX\n", \
				unsigned char:  "%*s" #val " == " "(unsigned char) 0x%hhX\n", \
				signed short:   "%*s" #val " == " "(signed short) 0x%hX\n", \
				unsigned short: "%*s" #val " == " "(unsigned char) 0x%hX\n", \
				signed int:     "%*s" #val " == " "(signed int) 0x%X\n", \
				unsigned int:   "%*s" #val " == " "(unsigned int) 0x%X\n", \
				signed long:    "%*s" #val " == " "(signed long) 0x%lX\n", \
				unsigned long:  "%*s" #val " == " "(unsigned long) 0x%lX\n", \
				float:          "%*s" #val " == " "(float) %#a\n", \
				double:         "%*s" #val " == " "(double) %#la\n", \
				long double:    "%*s" #val " == " "(long double) %#La\n", \
				default:        "%*s" #val " == " "(void*) %#p\n")), \
				debug_depth, "", val);
		
		#define dprint(val) \
			assert(debug_depth >= 0),\
			printf((_Generic(val, \
				bool:           "%*s" #val " == " "(bool) %hhi\n", \
				signed char:    "%*s" #val " == " "(signed char) %hhi\n", \
				unsigned char:  "%*s" #val " == " "(unsigned char) %hhu\n", \
				signed short:   "%*s" #val " == " "(signed short) %hi\n", \
				unsigned short: "%*s" #val " == " "(unsigned short) %hu\n", \
				signed int:     "%*s" #val " == " "(signed int) %i\n", \
				unsigned int:   "%*s" #val " == " "(unsigned int) %u\n", \
				signed long:    "%*s" #val " == " "(signed long) %li\n", \
				unsigned long:  "%*s" #val " == " "(unsigned long) %lu\n", \
				float:          "%*s" #val " == " "(float) %f\n", \
				double:         "%*s" #val " == " "(double) %lf\n", \
				long double:    "%*s" #val " == " "(long double) %Lf\n", \
				default:        "%*s" #val " == " "(void*) %p\n")), \
				debug_depth, "", val);
		
		#define ddprintf(format, ...) \
			assert(debug_depth >= 0),\
			printf("%*s" format, debug_depth, "", ## __VA_ARGS__)
		
	#else
		#define TODO assert(!"TODO");
		#define CHECK assert(!"CHECK");
		#define NOPE assert(!"NOPE");
		
		#define dpvs(x) ;
		#define dpv(x) ;
		#define dpvb(x) ;
		#define dpvc(x) ;
		#define dpvo(x) ;
		#define dpvsn(_, __) ;
		#define ddprintf(format, ... ) ;
		#define dpvc(x) ;
		
		#define ENTER
		#define HERE ;
		#define EXIT
	#endif
#else
	#define TODO assert(!"TODO");
	#define CHECK assert(!"CHECK");
	#define NOPE assert(!"NOPE");
	
	#define ENTER ;
	#define EXIT ;
	
	#define ddprintf(...) ;
	#define dpvb(x) ;
	#define dpv(x) ;
	#define dpvs(x) ;
	#define dpvc(x) ;
#endif

















