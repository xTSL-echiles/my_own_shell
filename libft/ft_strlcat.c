/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:55:32 by eoddish           #+#    #+#             */
/*   Updated: 2020/11/23 18:08:46 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	nd;
	size_t	n;
	size_t	i;

	nd = 0;
	i = 0;
	while (nd < dstsize && dst[nd] != '\0')
		nd++;
	n = dstsize - nd;
	if (n == 0)
		return (nd + ft_strlen(src));
	while (src[i] && n - 1)
	{
		dst[nd + i] = src[i];
		i++;
		n--;
	}
	dst[nd + i] = '\0';
	return (nd + ft_strlen(src));
}
