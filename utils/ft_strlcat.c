/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:40:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/03/07 16:43:32 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Appends string 'src' into string 'dst', up to a new string of 'max_size'
// Returns the size of the concatenated dst + the size of remaining src
// If not enough max_size, returns the minimum size it would need
size_t	ft_strlcat(char *dst, const char *src, size_t max_size)
{
	size_t	return_size;

	return_size = 0;
	while (*dst && return_size < max_size)
	{
		dst++;
		return_size++;
	}
	if (return_size >= max_size)
		return (return_size + ft_strlen(src));
	while (*src && return_size + 1 < max_size)
	{
		*dst = *src;
		dst++;
		src++;
		return_size++;
	}
	*dst = '\0';
	return (return_size + ft_strlen(src));
}
