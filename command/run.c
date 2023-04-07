
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <debug.h>

#include <defines/argv0.h>

#include <enums/error.h>

#include <memory/smalloc.h>

#include "simple/struct.h"

#include "struct.h"
#include "run.h"

bool command_run(
	struct command* this,
	int dirfd)
{
	bool error = false;
	ENTER;
	
	unsigned i, n = this->simples.n, fd;
	
	int (*pipes)[n-1][2] = smalloc(sizeof(*pipes));
	
	for (i = 0; i < n - 1; i++)
		pipes[0][i][0] = -1, pipes[0][i][1] = -1;
	
	for (i = 0; !error && i < n - 1; i++)
	{
		if (pipe2(pipes[0][i], O_CLOEXEC) < 0)
		{
			TODO;
			error = true;
		}
	}
	
	pid_t (*children)[n] = smalloc(sizeof(*children));
	
	for (i = 0; i < n; i++)
		children[0][i] = -1;
	
	for (i = 0; !error && i < n; i++)
	{
		pid_t child = fork();
		
		if (child < 0)
		{
			fprintf(stderr, "%s: fork(): %m\n", argv0),
			exit(e_syscall_failed);
		}
		else if (!child)
		{
			struct simple_command* simple = this->simples.data[i];
			
			if (fchdir(dirfd) < 0)
			{
				fprintf(stderr, "%s: fchdir(): %m\n", argv0);
				error = true;
			}
			
			if (!error && i == 0 && this->redirect_in)
			{
				int fd = open(this->redirect_in, O_RDONLY);
				
				if (fd < 0)
				{
					TODO;
					error = true;
				}
				else if (dup2(fd, 0) < 0)
				{
					TODO;
					error = true;
				}
			}
			
			if (!error && i + 1 == n && this->redirect_out)
			{
				int fd = open(this->redirect_out, O_WRONLY | O_CREAT | O_TRUNC, 0664);
				
				if (fd < 0)
				{
					TODO;
					error = true;
				}
				else if (dup2(fd, 1) < 0)
				{
					TODO;
					error = true;
				}
			}
			
			if (!error && execvp(*simple->args.data, simple->args.data) < 0)
			{
				fprintf(stderr, "%s: execvp(): %m\n", argv0);
				error = true;
			}
			
			exit(error);
		}
		else
		{
			children[0][i] = child;
		}
	}
	
	for (i = 0; i < n - 1; i++)
	{
		if ((fd = pipes[0][i][0]))
			close(fd);
		if ((fd = pipes[0][i][1]))
			close(fd);
	}
	
	for (i = 0; i < n; i++)
	{
		pid_t child = (*children)[i];
		
		if (child > 0)
		{
			int wstatus;
			
			if (waitpid(child, &wstatus, 0) < 0)
			{
				fprintf(stderr, "%s: waitpid(): %m\n", argv0),
				error = true;
			}
			else if (!WIFEXITED(wstatus) || WEXITSTATUS(wstatus))
			{
				error = true;
			}
		}
	}
	
	free(children);
	
	free(pipes);
	
	EXIT;
	return error;
}










