#include <stdio.h>
#include <sys/wait.h>

#include <unistd.h> // access execve
#include <string.h> // perror

int	main(int argc, char const *argv[], char **envp)
{

	const char *infile;
	int infile_access;

	if (argc != 3)
	{
		printf("wrong number of arguments");
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
	printf("My PID %i\n", pid);

	char *args[2];

	args[0] = "/bin/ls";        // first arg is the full path to the executable
	args[1] = {"-la";             // list of args must be NULL terminated

	if ( pid == 0 )
	{
		printf("I'm the kid: %i\n", pid);
		execve(args[0], args, envp);
	}
	else
	{
		printf("I'm the papa: %i\n", pid);
		wait(0);
		printf("PAPA OUT!\n");
	}
	return (0);
}
