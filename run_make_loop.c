
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

#include <debug.h>

#include <defines/argv0.h>

#include <enums/error.h>

#include <memory/srealloc.h>

#include <cmdln/options/jobs.h>
#include <cmdln/options/dry_run.h>

#include <database/struct.h>
#include <database/add_test_result.h>

#include <recipe/struct.h>

#include <dirfd/struct.h>

#include <recipeset/foreach.h>
/*#include <recipeset/is_empty.h>*/
/*#include <recipeset/discard.h>*/
#include <recipeset/any.h>

#include <heap/push.h>
#include <heap/is_nonempty.h>
#include <heap/pop.h>

#include <parse/zebu.h>

#include <misc/hsv_to_rgb.h>

#include "run_make_loop.h"

static bool file_exists(int dirfd, const char* path)
{
	return !faccessat(dirfd, path, F_OK, AT_SYMLINK_NOFOLLOW);
}

static time_t get_mtime(int dirfd, const char* path)
{
	struct stat buf = {};
	
	if (fstatat(dirfd, path, &buf, AT_SYMLINK_NOFOLLOW) < 0)
		return 0;
	else
		return buf.st_mtime;
}

static bool recipe_should_be_run(
	int dirfd,
	struct database* database,
	struct recipe* recipe)
{
	if (!file_exists(dirfd, recipe->target))
		return true;
	
	time_t mtime = get_mtime(dirfd, recipe->target);
	
	dpv(mtime);
	
	if (mtime <= database->header.too_old)
		return true;
	
	bool any = recipeset_any(recipe->dep_on, ({
		bool callback(const struct recipe* dependency) {
			time_t depmtime = get_mtime(dirfd, dependency->target);
			
			dpv(depmtime);
			
			return mtime < depmtime;
		}
		callback;
	}));
	
	return any;
}

void run_make_loop(
	struct recipeset* all_recipes,
	struct heap* ready,
	struct database* database)
{
	ENTER;
	
	recipeset_foreach(all_recipes, ({
		void callback(struct recipe* recipe)
		{
			if (recipe->execution.marked && !recipe->execution.waiting)
			{
				dpvs(recipe->target);
				
				heap_push(ready, recipe);
			}
		}
		callback;
	}));
	
	bool shutdown = false;
	
	void on_SIGINT(int signal)
	{
		char buffer[] = "SIGINT caught, shutting down...\n";
		
		write(1, buffer, sizeof(buffer));
		
		shutdown = true;
	}
	
	signal(SIGINT, on_SIGINT);
	
	unsigned jobs = cmdln_jobs;
	
	struct {
		fd_set set;
		unsigned n;
	} running = {}, finished = {};
	
	struct recipe* fd_to_recipe[FD_SETSIZE] = {};
	
	while (!shutdown && (running.n || heap_is_nonempty(ready)))
	{
		if (running.n)
		{
			finished = running;
			
			if (select(FD_SETSIZE, &finished.set, NULL, NULL, NULL) < 0)
			{
				if (errno != EINTR)
				{
					TODO;
					shutdown = true;
				}
			}
			else for (int fd = 0; fd < FD_SETSIZE; fd++)
			{
				if (FD_ISSET(fd, &finished.set))
				{
					dpv(fd);
					
					struct recipe* recipe = fd_to_recipe[fd];
					
					siginfo_t info;
					
					if (waitid(P_PIDFD, fd, &info, WEXITED) < 0)
					{
						fprintf(stderr, "%s: waitid(): %m\n", argv0);
						TODO;
						shutdown = true;
					}
					else if (WIFEXITED(info.si_status) && !WEXITSTATUS(info.si_status))
					{
						if (!cmdln_dry_run)
							database_add_test_result(database, recipe->target, recipe->dirfd, true);
						
						recipeset_foreach(recipe->dep_of, ({
							void callback(struct recipe* dep)
							{
								if (dep->execution.marked && !--dep->execution.waiting)
								{
									heap_push(ready, dep);
								}
							}
							callback;
						}));
					}
					else
					{
						fprintf(stderr, "%s: subcommand failed, shutting down...\n", argv0);
						
						database_add_test_result(database, recipe->target, recipe->dirfd, false);
						
						shutdown = true;
					}
					
					FD_CLR(fd, &running.set), running.n--;
					jobs++;
					
					close(fd);
				}
			}
		}
		
		while (!shutdown && jobs && heap_is_nonempty(ready))
		{
			struct recipe* recipe = heap_pop(ready);
			
			if (recipe_should_be_run(recipe->dirfd->fd, database, recipe))
			{
				pid_t pid;
				
				int fd;
				if ((pid = fork()) < 0)
				{
					// "fork() failed, shutting down..."
					TODO;
					shutdown = true;
				}
				else if (!pid)
				{
					if (recipe->commands)
					{
						struct {
							const char** data;
							unsigned n, cap;
						} argv = {};
						
						void append(const char* arg)
						{
							if (argv.n == argv.cap)
							{
								argv.cap = argv.cap << 1 ?: 1;
								argv.data = srealloc(argv.data, sizeof(*argv.data) * argv.cap);
							}
							
							argv.data[argv.n++] = arg;
						}
						
						struct rgb color = {128, 128, 128};
						
						if (recipe->scores.real >= 0)
							color = hsv_to_rgb((recipe->scores.real * 2 * M_PI) / 3, 0.9, 1);
						
						for (unsigned i = 0, n = recipe->commands->commands.n; i < n; i++)
						{
/*							printf("%5u ", jobs);*/
/*							printf("%6.2Lf%% ", recipe->scores.real * 100);*/
							printf("\e[38;2;%hhu;%hhu;%hhum$", color.red, color.green, color.blue);
							
							struct zebu_command* command = recipe->commands->commands.data[i];
							
							argv.n = 0;
							
							for (unsigned i = 0, n = command->args.n; i < n; i++)
							{
								const char* arg = (char*) command->args.data[i]->data;
								
								printf(" %s", arg);
								
								append(arg);
							}
							
							printf("\e[0m\n");
							
							append(NULL);
							
							if (!cmdln_dry_run)
							{
								pid_t child;
								int wstatus;
								
								if ((child = fork()) < 0)
								{
									fprintf(stderr, "%s: fork(): %m\n", argv0),
									exit(e_syscall_failed);
								}
								else if (!child)
								{
									if (fchdir(recipe->dirfd->fd) < 0)
									{
										fprintf(stderr, "%s: fchdir(): %m\n", argv0),
										exit(e_syscall_failed);
									}
									else if (execvp(argv.data[0], (void*) argv.data) < 0)
									{
										fprintf(stderr, "%s: execvp(): %m\n", argv0),
										exit(e_syscall_failed);
									}
								}
								else if (waitpid(child, &wstatus, 0) < 0)
								{
									fprintf(stderr, "%s: waitpid(): %m\n", argv0),
									exit(e_syscall_failed);
								}
								else if (!WIFEXITED(wstatus) || WEXITSTATUS(wstatus))
								{
									fprintf(stderr, "%s: error "
										"while attempting to build "
										"target '%s'\n", argv0, recipe->target);
									exit(e_syscall_failed);
								}
							}
						}
						
						free(argv.data);
					}
					exit(0);
				}
				else if ((fd = syscall(__NR_pidfd_open, pid, 0)) < 0)
				{
					fprintf(stderr, "%s: pidfd_open(): %m\n", argv0);
					shutdown = true;
				}
				else
				{
					dpv(pid);
					
					dpv(fd);
					
					FD_SET(fd, &running.set), running.n++;
					
					fd_to_recipe[fd] = recipe;
					
					jobs--;
				}
			}
			else
			{
				// printf("%s: target '%s' does not need to be rebuilt\n", argv0, recipe->target);
				
				recipeset_foreach(recipe->dep_of, ({
					void callback(struct recipe* dep)
					{
						if (dep->execution.marked && !--dep->execution.waiting)
						{
							heap_push(ready, dep);
						}
					}
					callback;
				}));
			}
		}
	}
	
	if (shutdown && running.n)
	{
		printf("%s: waiting for subprocesses to finish...\n", argv0);
		
		for (int fd = 0; fd < FD_SETSIZE; fd++)
		{
			if (FD_ISSET(fd, &running.set))
			{
				struct recipe* recipe = fd_to_recipe[fd];
				
				siginfo_t info;
				
				if (waitid(P_PIDFD, fd, &info, WEXITED) < 0)
				{
					fprintf(stderr, "%s: waitid(): %m\n", argv0);
					TODO;
				}
				else if (WIFEXITED(info.si_status) && !WEXITSTATUS(info.si_status))
				{
					database_add_test_result(database, recipe->target, recipe->dirfd, true);
				}
				else
				{
					database_add_test_result(database, recipe->target, recipe->dirfd, false);
				}
				
				close(fd);
			}
		}
	}

	EXIT;
}















