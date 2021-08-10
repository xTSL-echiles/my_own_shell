/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:41:20 by eoddish           #+#    #+#             */
/*   Updated: 2020/11/23 21:25:10 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "libft.h"

static void	ft_src_dst(size_t len, unsigned char *d, const unsigned char *s)
{
	int	i;

	i = len - 1;
	while (i >= 0)
	{
		d[i] = s[i];
		i--;
	}
}

static void	ft_dst_src(size_t len, unsigned char *d, const unsigned char *s)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d == s || len == 0)
		return (dst);
	if (d > s && d - s < (int)len)
	{
		ft_src_dst(len, d, s);
		return (dst);
	}
	else if (s > d && s - d < (int)len)
	{
		ft_dst_src(len, d, s);
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
