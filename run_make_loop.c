
#include <stdio.h>
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

#include <dirfd/struct.h>

#include <cmdln/options/jobs.h>

#include <commands/run.h>

#include <database/struct.h>
#include <database/update.h>

#include <heap/new.h>
#include <heap/push.h>
#include <heap/push.h>
#include <heap/is_nonempty.h>
#include <heap/pop.h>
#include <heap/free.h>

#include <recipe/struct.h>
#include <recipe/compare_scores.h>

#include <recipeset/any.h>
#include <recipeset/foreach.h>

#include "mark_recipes_for_execution.h"
#include "run_make_loop.h"

static bool recipe_should_be_run(
	struct dirfd* dirfd,
	struct database* database,
	struct recipe* recipe)
{
	struct stat buf = {};
	
	if (fstatat(dirfd->fd, recipe->target, &buf, AT_SYMLINK_NOFOLLOW) < 0)
	{
		if (errno == ENOENT)
		{
			return true;
		}
		else
		{
			TODO;
			exit(1);
		}
	}
	else if (buf.st_mtime < database->clean)
		return true;
	
	bool any = recipeset_any(recipe->dep_on, ({
		bool callback(const struct recipe* dependency)
		{
			struct stat subbuf = {};
			
			if (fstatat(dirfd->fd, dependency->target, &subbuf, AT_SYMLINK_NOFOLLOW) < 0)
			{
				return true;
			}
			
			return buf.st_mtime < subbuf.st_mtime;
		}
		callback;
	}));
	
	return any;
}

void run_make_loop(
	struct recipeset* all_recipes,
	struct database* database)
{
	ENTER;
	
	dpv(execution_round_id);
	
	struct heap* ready = new_heap(compare_recipe_scores);
	
	recipeset_foreach(all_recipes, ({
		void callback(struct recipe* recipe)
		{
			if (true
				&& recipe->execution.marked
				&& recipe->execution.round == execution_round_id
				&& !recipe->execution.waiting)
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
						
						database_update(database, recipe->target, recipe->dirfd);
						
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
			
			if (recipe->commands && recipe_should_be_run(recipe->dirfd, database, recipe))
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
					if (commands_run(recipe->commands, recipe->dirfd->fd))
					{
						fprintf(stderr, "%s: error "
							"while attempting to build "
							"target '%s'\n", argv0, recipe->target);
						exit(e_syscall_failed);
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
					FD_SET(fd, &running.set), running.n++;
					
					fd_to_recipe[fd] = recipe;
					
					jobs--;
				}
			}
			else
			{
/*				printf("%s: target '%s' does not need to be rebuilt\n", argv0, recipe->target);*/
				
				recipeset_foreach(recipe->dep_of, ({
					void callback(struct recipe* dep)
					{
						if (true
							&& dep->execution.marked
							&& dep->execution.round == execution_round_id
							&& !--dep->execution.waiting)
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
				else if (!WIFEXITED(info.si_status) || WEXITSTATUS(info.si_status))
				{
					database_update(database, recipe->target, recipe->dirfd);
				}
				
				close(fd);
			}
		}
	}
	
	free_heap(ready);
	
	EXIT;
}















