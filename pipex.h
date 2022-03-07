/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:41:00 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/03/07 16:46:34 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h> // malloc and free
# include <unistd.h> // write
# include <unistd.h> // access execve pipe
# include <stdio.h> // perror
# include <errno.h> // errno
# include <string.h> // strerror
# include <stdlib.h> // exit
# include <fcntl.h> // open

void	ft_exec(char *command, char **envp);
int		pipex(char **argv, char **envp);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t max_size);

#endif