/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:42:43 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/03/14 21:23:19 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	replace_spaces(char *str);
void	restore_spaces(char **exec_args);
int		is_quote(char c);
int		contains_quote_mark(char *str);
void	remove_quotes(char *str);

char	**get_exec_args(char *command)
{
	char	**exec_args;

	if (contains_quote_mark(command))
	{
		replace_spaces(command);
		remove_quotes(command);
		exec_args = ft_split(command, ' ');
		restore_spaces(exec_args);
	}
	else
		exec_args = ft_split(command, ' ');
	return (exec_args);
}

void	restore_spaces(char **exec_args)
{
	char	*str;

	while (*exec_args)
	{
		str = *exec_args;
		while (*str)
		{
			if (*str == -1)
				*str = ' ';
			str++;
		}
		exec_args++;
	}
	return ;
}

void	remove_quotes(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			*str = ' ';
		str++;
	}
}

void	replace_spaces(char *str)
{
	while (*str && !is_quote(*str))
		str++;
	if (*str)
		str++;
	while (*str && !is_quote(*str))
	{
		if (*str == ' ')
			*str = -1;
		str++;
	}
	if (*str)
		str++;
	if (*str)
		replace_spaces(str);
}

int	contains_quote_mark(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			return (1);
		str++;
	}
	return (0);
}
