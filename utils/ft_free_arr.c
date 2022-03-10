/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:17:38 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/03/10 16:34:12 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_arr(char	**arr)
{
	int	y;

	if (!arr)
		return ;
	y = 0;
	while (arr[y])
	{
		free(arr[y]);
		arr[y] = NULL;
		y++;
	}
	free(arr);
	arr = NULL;
	return ;
}
