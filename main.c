#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	if (argc != 5)
	{
		printf("Wrong number of arguments");
		return(1);
	}
	return(pipex(argv, envp));
}
