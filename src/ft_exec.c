/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:26:54 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/03/10 13:18:51 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "limits.h"

char	*get_executable(char *cmd, char **envp);
char	**get_paths(char **envp);

void	ft_exec(char *command, char **envp)
{
	char	*path;
	char	**exec_args;

	exec_args = ft_split(command, ' ');
	path = get_executable(exec_args[0], envp);
	execve(path, exec_args, envp);
	exit(errno);
}

char	*get_executable(char *cmd, char **envp)
{
	char	*executable;
	char	**paths;
	int		i;

	paths = get_paths(envp);
	executable = malloc(sizeof(char) * (PATH_MAX));
	i = 0;
	while (paths[i])
	{
		ft_strlcat(executable, paths[i], PATH_MAX);
		ft_strlcat(executable, "/", PATH_MAX);
		ft_strlcat(executable, cmd, PATH_MAX);
		if (access(executable, X_OK) == 0)
			break ;
		*executable = 0;
		i++;
	}
	if (executable && *executable)
		return (executable);
	ft_free_arr(paths);
	free(executable);
	write(STDERR_FILENO, "command not found: ", 19);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, "\n", 1);
	exit(0);
}

char	**get_paths(char **envp)
{
	char	*path_env;
	char	**paths;

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
