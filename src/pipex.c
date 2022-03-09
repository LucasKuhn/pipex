/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:37:18 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/03/09 16:06:41 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_exec(char **argv, char **envp, int *pipe_fds)
{
	int	infile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
		exit(1);
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipe_fds[1], STDOUT_FILENO);
	ft_exec(argv[2], envp);
}

void	parent_exec(char **argv, char **envp, int *pipe_fds)
{
	int	outfile_fd;

	close(pipe_fds[1]);
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(pipe_fds[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	ft_exec(argv[3], envp);
}

void	check_files_access(char **argv)
{
	if (access(argv[1], R_OK) == -1)
		perror(argv[1]);
	if (access(argv[4], W_OK) == -1)
		perror(argv[4]);
	return ;
}

int	pipex(char **argv, char **envp)
{
	pid_t	pid;
	int		pid_status;
	int		pipe_fds[2];

	check_files_access(argv);
	pipe(pipe_fds);
	pid = fork();
	if (pid == 0)
		child_exec(argv, envp, pipe_fds);
	else
	{
		pid_status = 0;
		waitpid(pid, &pid_status, 0);
		if (pid_status != 0)
			return (WEXITSTATUS(pid_status));
		parent_exec(argv, envp, pipe_fds);
	}
	return (0);
}
