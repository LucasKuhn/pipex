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
	write(STDERR_FILENO, "command not found: ", 19);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
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

void	child_exec(char **argv, char **envp, int *pipe_fds)
{
	char	*path;
	char	**exec_args;
	int		infile_fd;

	infile_fd = open(argv[1], O_RDONLY); // Opens the infile, access already checked

	dup2(infile_fd, STDIN_FILENO); // The stdin should come from the infile 
	dup2(pipe_fds[1], STDOUT_FILENO); // Stdout should go to the the pipe open exit
	exec_args = ft_split(argv[2], ' ');
	path = get_executable(exec_args[0], envp);
	execve(path, exec_args, envp);
	exit(errno);
}

void parent_exec(char **argv, char **envp, int *pipe_fds)
{
	int		outfile_fd;

	close(pipe_fds[1]);				// Close the exit used by the child
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777); // Opens the outfile for writing, creates it if doesn't exist, truncates the size to 0 to clear it, chmods 
	dup2(pipe_fds[0], STDIN_FILENO); // The stdin should come from the pipe entrance
	dup2(outfile_fd, STDOUT_FILENO); // Stdout should go to the the outfile
	
	char	**exec_args;
	char	*path;
	exec_args = ft_split(argv[3], ' ');
	path = get_executable(exec_args[0], envp);
	execve(path, exec_args, envp);
	exit(errno);
}

void check_files_access(char **argv)
{
	if (access(argv[1], R_OK) == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	if (access(argv[1], W_OK) == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	return ;
}

int	pipex(char **argv, char **envp)
{
	pid_t pid;
	int pid_status;
	int pipe_fds[2];

	check_files_access(argv);
	pipe(pipe_fds);
	pid = fork();

	if ( pid == 0 )
		child_exec(argv, envp, pipe_fds);
	else
	{
		pid_status = 0;
		waitpid(pid, &pid_status, 0);
		if (pid_status != 0)
			return(WEXITSTATUS(pid_status));
		parent_exec(argv, envp, pipe_fds);
	}
	return (0);
}
