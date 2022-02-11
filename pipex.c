#include "pipex.h"
#include "limits.h"

char **get_paths(char **envp)
{
	char *path_env;
	char **paths;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			break ;
		envp++;
	}
	path_env = *envp + 5;
	paths = ft_split(path_env, ':');
	return (paths);
}

char *get_executable(char *cmd, char **envp)
{
	char *executable;
	char **paths;
	int i;
	
	paths = get_paths(envp);
	executable = malloc(sizeof(char) * (PATH_MAX));
	i = 0;
	while (paths[i])
	{
		ft_strlcat(executable, paths[i], PATH_MAX);
		ft_strlcat(executable, "/", PATH_MAX);
		ft_strlcat(executable, cmd, PATH_MAX);
		if ( access(executable, X_OK) == 0 )
			break;
		*executable = 0;
		i++;
	}
	if (executable && *executable)
		return(executable);
	printf("%s: command not found\n", cmd);
	exit(127);
}

void print_arr(char **arr)
{
	int i;
	
	i = 0;
	while (arr[i])
	{
		printf("-->%s\n", arr[i]);
		i++;
	}
}

void	child_exec(char **argv, char **envp)
{
	char *path;
	char **exec_args;
	int infile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	dup2(infile_fd, STDIN_FILENO);
	exec_args = ft_split(argv[2], ' ');
	path = get_executable(exec_args[0], envp);
	printf("exec_args: \n");
	print_arr(exec_args);
	execve(path, exec_args, envp);
	exit(errno);
}

int	pipex(char **argv, char **envp)
{
	pid_t pid;
	int pid_status;

	if (access(argv[1], R_OK) == -1)
	{
		perror(argv[1]);
		return(1);
	}
	pid = fork();
	pid_status = 0;
	if ( pid == 0 )
		child_exec(argv, envp);
	else
	{
		waitpid(pid, &pid_status, 0);
		if (pid_status != 0)
			return(WEXITSTATUS(pid_status));
	}
	return (0);
}
