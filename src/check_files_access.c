/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files_access.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:05:05 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/03/14 19:05:24 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_files_access(char **argv)
{
	if (access(argv[1], R_OK) == -1)
		perror(argv[1]);
	if (access(argv[4], F_OK) == -1)
		return ;
	if (access(argv[4], W_OK) == -1)
		perror(argv[4]);
	return ;
}

void	check_argc_count(int argc)
{
	if (argc != 5)
	{
		write(1, "Wrong number of arguments\n", 26);
		exit(EXIT_FAILURE);
	}
}
