/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:26:54 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/03/15 15:18:33 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"
#include "pipex.h"

char	*get_exec_path(char **exec_args, char **envp);
char	**get_paths(char **envp);

void	ft_exec(char *command, char **envp)
{
	char	*exec_path;
	char	**exec_args;

	exec_args = get_exec_args(command);
	exec_path = get_exec_path(exec_args, envp);
	execve(exec_path, exec_args, envp);
	exit(errno);
}

char	*get_exec_path(char **exec_args, char **envp)
{
	char	*exec_path;
	char	**paths;
	int		i;

	paths = get_paths(envp);
	exec_path = malloc(sizeof(char) * (PATH_MAX));
	i = 0;
	while (paths[i])
	{
		ft_strlcat(exec_path, paths[i], PATH_MAX);
		ft_strlcat(exec_path, "/", PATH_MAX);
		ft_strlcat(exec_path, exec_args[0], PATH_MAX);
		if (access(exec_path, X_OK) == 0)
			break ;
		*exec_path = 0;
		i++;
	}
	if (exec_path && *exec_path)
		return (exec_path);
	write(STDERR_FILENO, "command not found: ", 19);
	write(STDERR_FILENO, exec_args[0], ft_strlen(exec_args[0]));
	write(STDERR_FILENO, "\n", 1);
	ft_free_arr(paths);
	ft_free_arr(exec_args);
	exit(127);
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
