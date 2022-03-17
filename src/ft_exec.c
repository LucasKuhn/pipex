/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:26:54 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/03/17 09:20:05 by lalex-ku         ###   ########.fr       */
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
	exit(EXIT_FAILURE);
}

char	*get_exec_path(char **exec_args, char **envp)
{
	char	*exec_path;
	char	**paths;
	int		i;

	paths = get_paths(envp);
	exec_path = malloc(sizeof(char) * (PATH_MAX + 1));
	i = 0;
	while (paths[i])
	{
		ft_strlcat(exec_path, paths[i], PATH_MAX);
		ft_strlcat(exec_path, "/", PATH_MAX);
		ft_strlcat(exec_path, exec_args[0], PATH_MAX);
		if (access(exec_path, X_OK) == 0)
		{
			ft_free_arr(paths);
			return (exec_path);
		}
		*exec_path = 0;
		i++;
	}
	print_error(exec_args[0], "command not found");
	ft_free_arr(paths);
	ft_free_arr(exec_args);
	free(exec_path);
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
