/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:41:00 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/03/16 15:40:43 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h> // malloc and free
# include <unistd.h> // access execve pipe write dup2 fork
# include <stdio.h> // perror
# include <string.h> // strerror
# include <stdlib.h> // exit
# include <fcntl.h> // open
# include <sys/wait.h> // waitpid

void	ft_exec(char *command, char **envp);
int		pipex(int argc, char **argv, char **envp);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t max_size);
void	ft_free_arr(char **arr);
char	**get_exec_args(char *command);
void	check_files_access(char **argv);
void	check_argc_count(int argc);
int		is_quote(char c);
void	print_error(char *cmd, char *message);

#endif