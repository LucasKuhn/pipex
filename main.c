#include <sys/wait.h>
#include <string.h>

#include <unistd.h> // access execve
#include <stdio.h>  // perror
#include <stdlib.h> // exit
#include <errno.h>

#include "pipex.h"

int	main(int argc, char const *argv[], char **envp)
{	
	const char *infile;
	int infile_access;
	char *path;

	if (argc != 3)
	{
		printf("Wrong number of arguments");
		return(1);
	}
	infile = argv[1];
	infile_access = access(infile, R_OK);
	if (infile_access == -1)
	{
		perror(infile);
		return(1);
	}	

	pid_t pid = fork();

	if ( pid == 0 )
	{
		printf("\n🐣 pid here is %i \n", pid);
		while (*envp)
		{
			if (ft_strncmp(*envp, "PATH=", 5) == 0)
				path = *envp + 5;
			envp++;
		}
		char **paths;
		char filename[1024];
		paths = ft_split(path, ':');
		while (*paths)
		{
			printf("path -> %s\n", *paths);
			strcpy(filename, (const char *)*paths);
			ft_strlcat(filename, "/", 1024);
			ft_strlcat(filename, argv[2], 1024);
			printf("filename -> %s\n", filename);
			if ( access(filename, X_OK) == 0 )
				break;
			*filename = 0;
			paths++;
		}
		if (!*filename)
		{
			printf("%s: command not found\n", argv[2]);
			exit(127);
		}
		char *args[] = { filename, (char *)argv[1], 0 };
		printf("🐣 -- executing --\n");
		execve(args[0], args, envp);
		perror("🐣 execve"); 
		printf("🐣 Errorno here is: %i\n", errno);
		exit(errno);
	}
	else
	{
		int wstatus = 0;
		printf("\n👴 pid here is %i \n", pid);
		waitpid(pid, &wstatus, 0);
		if (wstatus != 0)
		{
			perror("\n👴 waitpid"); 
			printf("\n👴 Something bad happened -> wstatus: %i (%i)\n", wstatus, WEXITSTATUS(wstatus));
			return(WEXITSTATUS(wstatus));
		}
		printf("\n👴 PAPA OUT! ✌️\n");
	}
	return (0);
}